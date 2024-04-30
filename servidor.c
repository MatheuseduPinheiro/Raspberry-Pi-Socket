#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <errno.h> // Adicionado para a variável errno
#include <time.h>  // Para a função time

#define PORT 8080
#define BUFFER_SIZE 1024
#define SAVE_PATH "/home/raspmat/Documentos/lingc/communication"

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    // Criar socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket falhou");
        exit(EXIT_FAILURE);
    }

    // Configurar endereço e porta
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind falhou");
        exit(EXIT_FAILURE);
    }

    // Listen
    if (listen(server_fd, 3) < 0) {
        perror("Listen falhou");
        exit(EXIT_FAILURE);
    }

    printf("Aguardando conexão...\n");

    // Aceitar conexão
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
        perror("Accept falhou");
        exit(EXIT_FAILURE);
    }

    printf("Conexão estabelecida!\n");

    // Verifique se o caminho do diretório existe antes de tentar criar
    struct stat stat_buf;
    if (stat(SAVE_PATH, &stat_buf) < 0) { // Verifica se o caminho existe
        if (mkdir(SAVE_PATH, 0755) < 0 && errno != EEXIST) {
            perror("Erro ao criar diretório");
            close(new_socket);
            close(server_fd);
            exit(EXIT_FAILURE);
        }
    }

    // Criar nome do arquivo com base no tempo para evitar colisões
    time_t now = time(NULL); 
    char file_name[256];
    snprintf(file_name, sizeof(file_name), "%s/arquivo_recebido_%ld.txt", SAVE_PATH, now);

    // Criar arquivo para salvar os dados recebidos
    FILE *file = fopen(file_name, "wb");
    if (!file) {
        perror("Falha ao criar arquivo");
        close(new_socket);
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Receber dados e escrever no arquivo
    ssize_t bytes_received;
    while ((bytes_received = read(new_socket, buffer, BUFFER_SIZE)) > 0) {
        fwrite(buffer, 1, bytes_received, file);
    }

    fclose(file);
    close(new_socket);
    close(server_fd);

    printf("Arquivo recebido com sucesso e salvo em %s!\n", file_name);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER_IP "127.0.0.1" // IP do servidor
#define PORT 8080
#define BUFFER_SIZE 1024

void send_file(const char *file_path, int sock);

int main() {
    int sock;
    struct sockaddr_in server_address;

    // Criar socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket falhou");
        exit(EXIT_FAILURE);
    }

    // Configurar endereço e porta do servidor
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    if (inet_pton(AF_INET, SERVER_IP, &server_address.sin_addr) <= 0) {
        perror("Endereço inválido");
        close(sock);
        exit(EXIT_FAILURE);
    }

    // Conectar ao servidor
    if (connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Conexão falhou");
        close(sock);
        exit(EXIT_FAILURE);
    }

    printf("Conexão estabelecida com o servidor.\n");

    // Caminho do arquivo a ser enviado
    const char *file_path = "/home/raspmat/Desktop/pasta_teste/teste.txt";

    // Adicionar mensagem de depuração para verificar o caminho do arquivo
    printf("Tentando abrir o arquivo: %s\n", file_path);

    send_file(file_path, sock); // Enviar o arquivo para o servidor

    // Fechar a conexão
    close(sock);

    return 0;
}

void send_file(const char *file_path, int sock) {
    printf("Abrindo arquivo: %s\n", file_path); // Depuração para verificar o arquivo

    FILE *file = fopen(file_path, "rb"); // Abrir arquivo para leitura binária
    if (!file) {
        perror("Falha ao abrir arquivo"); // Mensagem de erro detalhada
        return;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    // Ler do arquivo e enviar pelo socket
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        if (send(sock, buffer, bytes_read, 0) < 0) {
            perror("Falha ao enviar dados"); // Tratamento de erro ao enviar dados
            fclose(file); // Fechar o arquivo se houver falha
            return;
        }
    }

    printf("Arquivo enviado com sucesso!\n"); // Confirmação de envio bem-sucedido
    fclose(file); // Fechar o arquivo após o envio
}

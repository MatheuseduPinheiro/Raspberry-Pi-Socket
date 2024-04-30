# RaspiFileTransfer


![simbulo raspb](https://github.com/MatheuseduPinheiro/RaspiFileTransfer/assets/100390250/c4089289-d2bd-409d-8f3a-53a145820669)


Este projeto trata da criação de um sistema de transferência de arquivos entre duas Raspberry Pis utilizando sockets usando a linguagem c. O sistema é baseado em uma arquitetura cliente-servidor, onde uma Raspberry Pi atua como servidor, aguardando conexões, enquanto a outra atua como cliente, enviando arquivos para o servidor.

## Contexto

O projeto faz parte da iniciativa de iniciação científica do CNPq em colaboração com a Universidade da Amazônia. O objetivo é explorar métodos eficazes de comunicação entre dispositivos Raspberry Pi para aplicações de transferência de dados e automação.

## Funcionalidades

- Transferência de arquivos entre duas Raspberry Pis usando sockets TCP (também pode ser usada a conexão local 127.0.0.1).
- Capacidade de lidar com arquivos de diversos tamanhos.
- Opção para personalizar portas e endereços IP para flexibilidade no ambiente de rede.


![Capturar](https://github.com/MatheuseduPinheiro/RaspiFileTransfer/assets/100390250/19c1684f-a40c-4462-a48a-1e2041317bfd)



## Requisitos

Para rodar este projeto, você precisará de:

- Duas Raspberry Pis (qualquer modelo com suporte a rede).
- Compilador C (como GCC) instalado em ambas as Raspberry Pis.
- Ambiente Raspbian ou semelhante.
- Atentar ao path onde se encontram as pastas.



// tcpserver.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 9090
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char *serverMessage = "Olá, mensagem do servidor!";
    
    // Criado o socket do servidor (IPv4, TCP)
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("Falha ao criar o socket");
        exit(EXIT_FAILURE);
    }
    
    // Endereço e Porta definidos
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;  // Aceita conexões de qualquer IP
    address.sin_port = htons(PORT);  // Converte para o formato de porta de rede
    
    // Ligado o socket ao endereço e porta especificados
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Falha no bind");
        exit(EXIT_FAILURE);
    }

    // Á escuta por conexões (limite de 3 conexões simultâneas na fila)
    if (listen(server_fd, 3) < 0) {
        perror("Falha ao ouvir");
        exit(EXIT_FAILURE);
    }
    printf("Á escuta por conexões...\n");

    // Aceitar a conexão do cliente
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    if (new_socket < 0) {
        perror("Falha ao aceitar conexão");
        exit(EXIT_FAILURE);
    }
    printf("Conexão aceita de %s:%d\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));
    
    // O servidor recebe a mensagem do cliente
    int bytes_read = read(new_socket, buffer, BUFFER_SIZE);
    if (bytes_read > 0) {
        printf("Cliente: %s\n", buffer);
    } else {
        perror("Falha ao ler mensagem");
    }

    // O servidor envia uma mensagem para o cliente
    send(new_socket, serverMessage, strlen(serverMessage), 0);
    printf("Mensagem enviada para o cliente.\n");
    
    // Fechar a conexão e o socket
    close(new_socket);
    close(server_fd);
    return 0;
}
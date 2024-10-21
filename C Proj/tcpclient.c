// tcpclient.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 9090
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char *clientMessage = "Olá, mensagem do cliente!";
    char buffer[BUFFER_SIZE] = {0};
    
    // Criado o socket do cliente (IPv4, TCP)
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        printf("Falha ao criar o socket\n");
        return -1;
    }
    
    // Endereço do servidor definido
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    
    // Convertendo o endereço IP do servidor (localhost, 127.0.0.1)
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("Endereço inválido ou não suportado\n");
        return -1;
    }
    
    // Tentar conectar ao servidor
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Falha na conexão\n");
        return -1;
    }

    // O Cliente envia uma mensagem para o servidor
    send(sock, clientMessage, strlen(clientMessage), 0);
    printf("Mensagem enviada: %s\n", clientMessage);
    
    // O Cliente recebe a resposta do servidor
    int bytes_read = read(sock, buffer, BUFFER_SIZE);
    if (bytes_read > 0) {
        printf("Servidor: %s\n", buffer);
    } else {
        printf("Falha ao receber resposta\n");
    }
    
    // Fechar o socket
    close(sock);
    return 0;
}

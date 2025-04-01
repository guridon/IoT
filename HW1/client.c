#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(int argc, char *argv[]){
    int sock;
    struct sockaddr_in serv_addr;
    char message[30];
    int str_len;
    if (argc != 3) {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        error_handling("socket() error");
    }
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("connect() error");
    }
    str_len = read(sock, message, sizeof(message) - 1);
    if (str_len == -1) {
        error_handling("read() error");
    }
    printf("Message from server: %s\n", message);
    close(sock);
    return 0;   
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

// This code is a simple TCP client that connects to a server at a specified IP address and port.
// It reads a message from the server and prints it to the console.
// The client uses the socket API to create a socket, connect to the server, and read data from the server.
// The client uses the IPv4 address family (AF_INET) and TCP protocol (SOCK_STREAM).
// The client handles errors by printing an error message and exiting.  
// The client uses the inet_addr function to convert the IP address from a string to a network byte order.
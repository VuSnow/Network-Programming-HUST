#include <arpa/inet.h> /* These are usual header files. */
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFF_SIZE 1024

int client_sock;
int flag = 0;
char buff[BUFF_SIZE];
int bytes_sent, bytes_received, sin_size;

struct sockaddr_in server;
struct sockaddr_in client;


int main(int argc, char *argv[]) {
    
    // check input
    if(argc != 3){
        fprintf(stderr, "Usage: %s <IP address> <PORT Number>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *ip_address = argv[1];
    int port_number = atoi(argv[2]);

    // 1. Construct a UDP socket
    if((client_sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        perror("Socket creation failed\n");
        exit(EXIT_FAILURE);
    }

    // 2. Define address of server
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(port_number);
    server.sin_addr.s_addr = inet_addr(ip_address);

    // printf("Connect Successfully!\n");

    // 3. Join Server 
    while(1){
        sprintf(buff, "Hello, server\n");
        sin_size = sizeof(struct sockaddr_in);

        // printf("%s\n", buff);

        bytes_sent = sendto(client_sock, buff, strlen(buff), 0, (struct sockaddr *)&server, sin_size);
        // printf("bytes send: %d\n", bytes_sent);
        if(bytes_sent < 0){
            perror("Send Failed\n");
            continue;
        }

        bytes_received = recvfrom(client_sock, buff, BUFF_SIZE - 1, 0, (struct sockaddr *)&server, &sin_size);
        // printf("bytes received: %d\n", bytes_received);
        if(bytes_received < 0){
            perror("Receive Failed\n");
            continue;
        }

        // printf("%d\n", strstr(buff, "Hello, server") == NULL);
        if(strstr(buff, "Hello, server") == NULL){
            buff[bytes_received] = '\0';
            printf("%s\n", buff);
            break;
        }

        sleep(1);
    }

    // communicate with server
    pid_t child_id = fork();
    if (child_id == 0) {
        while (1) {
            memset(buff, '\0', (strlen(buff) + 1));
            fgets(buff, BUFF_SIZE, stdin);
            if (buff[strlen(buff) - 1] == '\n') {
                buff[strlen(buff) - 1] = '\0';
            }
            if (strcmp(buff, "") == 0) {
                close(client_sock);
                kill(getppid(), SIGKILL);
                exit(EXIT_SUCCESS);
            }

            sin_size = sizeof(struct sockaddr_in);
            bytes_sent = sendto(client_sock, buff, strlen(buff), 0,
                                (struct sockaddr *)&server, sin_size);
            if (bytes_sent < 0) {
                perror("\nError: ");
                close(client_sock);
                exit(EXIT_FAILURE);
            }
        }
    } else {
        while (1) {
            memset(buff, '\0', (strlen(buff) + 1));

            sin_size = sizeof(struct sockaddr_in);
            bytes_received = recvfrom(client_sock, buff, BUFF_SIZE - 1, 0,
                                      (struct sockaddr *)&server, &sin_size);
            if (bytes_received < 0) {
                perror("\nError: ");
                close(client_sock);
                exit(EXIT_FAILURE);
            }

            buff[bytes_received] = '\0';
            if (buff[bytes_received - 1] == '\n') {
                buff[bytes_received - 1] = '\0';
            }
            printf("%s\n", buff);
        }
    }

    close(client_sock);
    return 0;
}
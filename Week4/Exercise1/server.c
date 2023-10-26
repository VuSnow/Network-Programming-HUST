#include <arpa/inet.h> /* These are the usual header files */
#include <ctype.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define CMD_SIZE 1024
#define MSG_SIZE 8192
#define RES_SIZE CMD_SIZE + MSG_SIZE
int LISTENQ = 8;
int PORT_NUM, listen_sock, conn_sock;
char res[RES_SIZE];
struct sockaddr_in server;
struct sockaddr_in client;
int bytes_sent, bytes_received, sin_size;

int main(int argc, char *argv[]){
    if(argc != 2){
        fprintf(stderr, "Usage: ./server PORT_NUMBER\n");
        exit(EXIT_FAILURE);
    }
    PORT_NUM = atoi(argv[1]);

    // 1. Construct a TCP socket to listen connection request
    if((listen_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("Error!\n");
        exit(EXIT_FAILURE);
    }

    // 2. bind address to socket
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT_NUM);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(listen_sock, (struct sockaddr *)&server, sizeof(server)) == -1){
        perror("Bind error!\n");
        exit(EXIT_FAILURE);
    }

    // 3. Listen request from client
    if(listen(listen_sock, LISTENQ) == -1){
        perror("Listen error!\n");
        exit(EXIT_FAILURE);
    }

    // 4. Communicate with client
    while(1){
        sin_size = sizeof(struct sockaddr_in);
        if((conn_sock = accept(listen_sock, (struct sockaddr *)&client, &sin_size)) == -1){
            perror("Accept error!\n");
        }
        printf("Client [%s:%d] connected!\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

        // Start conversation
        while(1){
            // Receives messge from client
            memset(res, 0, RES_SIZE);
            bytes_received = recv(conn_sock, res, RES_SIZE, 0);
            if(bytes_received <= 0){
                printf("Connection closed!\n");
                break;
            }else{
                res[bytes_received] = '\0';
                printf("Received message from client: %s\n",res);
            }
        }
    }
}
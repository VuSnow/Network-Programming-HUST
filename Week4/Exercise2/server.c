#include <arpa/inet.h> /* These are the usual header files */
#include <ctype.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_FILE_SIZE (100 * 1024 * 1024) // 100MB
#define BUFFER_SIZE 1024

int LISTENQ = 8;
int PORT_NUM, server_sock, client_sock;
int file_size;
struct sockaddr_in server;
struct sockaddr_in client;
socklen_t  client_len = sizeof(client);
int bytes_sent, bytes_received, sin_size;
const char* SAVE_FOLDER = "received_files/";

int main(int argc, char *argv[]){
    if(argc != 2){
        fprintf(stderr, "Usage: ./server PORT_NUMBER\n");
        exit(EXIT_FAILURE);
    }
    PORT_NUM = atoi(argv[1]);

    // 1. Construct a TCP socket to listen connection request
    if((server_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("Error!\n");
        exit(EXIT_FAILURE);
    }

    // 2. bind address to socket
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT_NUM);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(server_sock, (struct sockaddr *)&server, sizeof(server)) == -1){
        perror("Bind error!\n");
        exit(EXIT_FAILURE);
    }

    // 3. Listen request from client
    if(listen(server_sock, LISTENQ) == -1){
        perror("Listen error!\n");
        exit(EXIT_FAILURE);
    }

    // 4. Communicate with client
    while(1){
        if((client_sock = accept(server_sock, (struct sockaddr *)&client, &client_len)) == -1){
            perror("Accept error!\n");
        }

        printf("Client [%s:%d] connected!\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
        
        char file_name[BUFFER_SIZE];
        bytes_received = recv(client_sock, file_name, sizeof(file_name),0);
        if(bytes_received <= 0){
            close(client_sock);
            continue;
        }

        char full_path[BUFFER_SIZE];
        snprintf(full_path, sizeof(full_path), "%s%s", SAVE_FOLDER, file_name);


        FILE *file = fopen(full_path, "r");
        if(file){
            fclose(file);
            send(client_sock, "EXISTED", 7, 0);
            close(client_sock);
            continue;
        }

        send(client_sock, "Ready to receive", 16, 0);

        file = fopen(full_path, "wb");
        if (file == NULL) {
            perror("Error opening file");
            close(client_sock);
            continue;
        }

        while (1) {
            char buffer[1024];
            int bytes_received = recv(client_sock, buffer, sizeof(buffer), 0);
            if (bytes_received <= 0) {
                fclose(file);
                close(client_sock);
                break;
            }
            fwrite(buffer, 1, bytes_received, file);
        }
        printf("File received: %s\n", file_name);
        close(client_sock);
    }

    close(server_sock);
    return 0;
}

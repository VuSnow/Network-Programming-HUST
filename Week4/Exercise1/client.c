#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>

#define CMD_SIZE 1024
#define MSG_SIZE 8192
#define REQ_SIZE CMD_SIZE + MSG_SIZE
#define RES_SIZE CMD_SIZE + MSG_SIZE

int client_sock;
char req_cmd[CMD_SIZE], req_msg[MSG_SIZE], req[REQ_SIZE], res[RES_SIZE];
struct sockaddr_in server_addr;
int bytes_sent, bytes_received, sin_size;

int main(int argc, char *argv[]){
    if(argc != 3){
        fprintf(stderr, "Usage: ./client IP_ADDRESS PORT_NUMBER\n");
        exit(EXIT_FAILURE);
    }
    char *SERVER_IP = argv[1];
    int SERVER_PORT = atoi(argv[2]);

    // 1. Construct socket
    if((client_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("Problem in creating the socket\n");
        exit(EXIT_FAILURE);
    }
    client_sock = socket(AF_INET, SOCK_STREAM, 0);

    // 2. Specify server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // 3. Request to connect server
    if(connect(client_sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) < 0){
        perror("Problem in connecting to server\n");
        exit(EXIT_FAILURE);
    }

    printf("Connect to server sucessfully!\n");

    // 4. send message to server
    while(1){
        printf("Insert string to send to server. \n");
        memset(req_msg, '\0', MSG_SIZE);
        fgets(req_msg, MSG_SIZE, stdin);
        if (req_msg[strlen(req_msg) - 1] == '\n') {
            req_msg[strlen(req_msg) - 1] = '\0';
        }

        int msg_len = strlen(req_msg);
        if(msg_len == 0){
            printf("Disconnect!\n");
            break;
        }

        bytes_sent = send(client_sock, req, REQ_SIZE, 0);
        if(bytes_sent <= 0){
            perror("Error sending request to server\n");
            break;
        }

        bytes_received = recv(client_sock, res, RES_SIZE, 0);
        if(bytes_received <= 0){
            perror("Error! Cannot receive reply from server!");
            break;
        }

        res[bytes_received] = '\0';
        printf("Reply from server: %s\n", res);
    }
}
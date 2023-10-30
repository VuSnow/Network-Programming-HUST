#include <arpa/inet.h> /* These are usual header files. */
#include <ctype.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFF_SIZE 1024

int split(char *alpha, char *numeric, char *input){
    int a_in = 0, n_in = 0;
    for(int i = 0; i < strlen(input); i++){
        if(isalpha(input[i])){
            alpha[a_in] = input[i];
            a_in++;
        }else if(isdigit(input[i])){
            numeric[n_in] = input[i];
            n_in++;
        }else{
            return 0;
        }
    }
    alpha[a_in] = '\0';
    numeric[n_in] = '\0';
    return 1;
}

int main(int argc, char *argv[]) {
    if(argc != 2){
        fprintf(stderr, "Usage: server\n");
        fprintf(stderr, "Usage: server PORT\n");
        exit(EXIT_FAILURE);
    }

    int server_sock;
    char buff[BUFF_SIZE];
    struct sockaddr_in server; // Server's address information
    struct sockaddr_in client; // Client's address information
    int bytes_sent, bytes_received, sin_size;

    // 1. Construct UDP socket
    if((server_sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
        perror("Socket error");
        exit(EXIT_FAILURE);
    }

    // 2. Bind address to socket
    int port_num = atoi(argv[1]);
    server.sin_family = AF_INET;
    server.sin_port = htons(port_num);
    server.sin_addr.s_addr = INADDR_ANY;
    bzero(&(server.sin_zero), 8);

    if(bind(server_sock, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1){
        perror("\nError: ");
        exit(EXIT_FAILURE);
    }

    // 3. Communicate with client
    int num_client = 0;
    // struct sockaddr_in client;
    while(num_client < 1){
        memset(buff, '\0', (strlen(buff) + 1));
        sin_size = sizeof(struct sockaddr);
        bytes_received = recvfrom(server_sock, buff, BUFF_SIZE - 1, 0, (struct sockaddr *)&client, &sin_size);

        if(bytes_received < 0){
            perror("Error\n");
            continue;
        }

        printf("Client connected: [%s:%d]\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
        num_client++;

        if(num_client == 1){
            sprintf(buff, "Status: Server connected. Start chatting!");
            bytes_sent = sendto(server_sock, buff, strlen(buff), 0, (struct sockaddr *)&client, sin_size);
            if(bytes_sent < 0){
                perror("\nError: ");
                close(server_sock);
                exit(EXIT_FAILURE);
            }
        }
    }
    while(1){
        memset(buff, '\0', (strlen(buff) + 1));

        sin_size = sizeof(struct sockaddr_in);
        bytes_received = recvfrom(server_sock, buff, BUFF_SIZE - 1, 0, (struct sockaddr *)&client, &sin_size);
        if(bytes_received < 0){
            perror("\nError");
        }else{
            buff[bytes_received] = '\0';
            printf("ReceiveMsg from [%s:%d]:%s\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port), buff);
        }

        char msg[BUFF_SIZE];
        memset(msg, '\0', (strlen(msg) + 1));
        char digits[BUFF_SIZE];
        memset(digits, '\0', (strlen(digits) + 1));
        char alphas[BUFF_SIZE];
        memset(alphas, '\0', (strlen(alphas) + 1));
        // printf("%s", buff);
        int isInvalid = 0;
        int digit_len = 0;
        int alpha_len = 0;
        for(int i = 0; i < bytes_received; i++){
            if(isdigit(buff[i])){
                digits[digit_len++] = buff[i];
            }else if(isalpha(buff[i])){
                alphas[alpha_len++] = buff[i];
            }else{
                isInvalid = 1;
                break;
            }
        }

        if(isInvalid){
            sprintf(buff, "Server: Only digits and alphabets are allowed!");
            bytes_sent = sendto(server_sock, buff, strlen(buff), 0, (struct sockaddr *)&client, sin_size);
            if(bytes_sent < 0){
                perror("\nError: ");
                close(server_sock);
                exit(EXIT_FAILURE);
            }
            continue;
        }    

        // Create message
        digits[digit_len] = '\0';
        alphas[alpha_len] = '\0';
        if (digit_len != 0 && alpha_len != 0) {
            sprintf(msg, "digits:%s\nalphabet:%s", digits, alphas);
        } else if (digit_len != 0) {
            strcpy(msg, digits);
        } else if (alpha_len != 0) {
            strcpy(msg, alphas);
        } else {
            strcpy(msg, "");
        }

        // Send message to client
        bytes_sent = sendto(server_sock, msg, strlen(msg), 0, (struct sockaddr *) &client, sin_size);
        if(bytes_sent < 0){
            perror("\nError: ");
            close(server_sock);
            exit(EXIT_FAILURE);
        }
    }

    close(server_sock);
    return 0;
}
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>

#define BUFFER_SIZE 1024
#define MAX_FILE_SIZE (100*1024*1024) //100MB

int client_sock;
struct sockaddr_in server_addr;
char file_path[BUFFER_SIZE];
int bytes_sent, bytes_received, sin_size;

int main(int argc, char *argv[]){
    if(argc != 3){
        printf("Usage: ./client IP_address PORT_number");
    }

    char *SERVER_IP = argv[1];
    int SERVER_PORT = atoi(argv[2]);

    // 1.Construct socket
    if((client_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("Problem in creating the socket\n");
        exit(EXIT_FAILURE);
    }

    // 2.Specify server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // 3.Request to connect server
    if(connect(client_sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) < 0){
        perror("Problem in connecting server\n");
        exit(EXIT_FAILURE);
    }

    printf("Connect to server successfully\n");

    // 4.Send file to server
    while(1){
        // Input the file path
        printf("Insert file path to send to server ");
        if(fgets(file_path, sizeof(file_path), stdin) == NULL || file_path[0] == '\n'){
            break;
        }

        // Remove the end line of the file path
        file_path[strcspn(file_path, "\n")] = '\0';

        // Open the file
        FILE *file = fopen(file_path, "rb");
        if(file == NULL){
            printf("File is not existed!\n");
            continue;
        }

        // Check the file size
        fseek(file, 0, SEEK_END);
        long long file_size = ftell(file);
        fseek(file, 0, SEEK_SET);

        if(file_size > MAX_FILE_SIZE){
            printf("File is too large to send (greater than 100MB)\n");
            fclose(file);
            continue;
        }

        // Send the file name to the server
        send(client_sock, file_path, strlen(file_path), 0);

        // Check the response of the server
        char response[20];
        recv(client_sock, response, sizeof(response), 0);

        if(strcmp(response, "EXISTED") == 0){
            printf("File already existed on the server: %s\n", file_path);
            fclose(file);
            continue;
        }

        // Read and send the file content
        char buffer[BUFFER_SIZE];
        int bytes_read;

        while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
            send(client_sock, buffer, bytes_read, 0);
        }

        fclose(file);

        send(client_sock, "Sent Successfully", 17, 0);
        // If file sent successfully, print file sent
        printf("File sent: %s\n", file_path);

    }
    close(client_sock);
    return 0;
}
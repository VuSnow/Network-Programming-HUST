#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdbool.h>
#include<netdb.h>

#define BUFF_SIZE 1024

int server_sock;
char buff[BUFF_SIZE];
struct sockaddr_in server;
struct sockaddr_in client;
int bytes_sent, bytes_received, sin_size;

struct in_addr ip_addr;
struct hostent *host;
struct hostent *test_host;
struct in_addr **addr_list;

bool is_valid_ip(char *ip){
  struct in_addr ipv4_addr;
  return inet_pton(AF_INET, ip, &ipv4_addr) != 0;
}

int main(int argc, char *argv[]){
    if(argc != 2){
        fprintf(stderr, "%s server\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // 1. Construct UDP socket
    if((server_sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
        perror("Socket Error!");
        exit(EXIT_FAILURE);
    }

    // 2. Bind address to socket
    int port_num = atoi(argv[1]);
    server.sin_family = AF_INET;
    server.sin_port = htons(port_num);
    server.sin_addr.s_addr = INADDR_ANY;
    bzero(&(server.sin_zero), 8);

    if(bind(server_sock, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1){
        perror("Binding Error! \n");
        exit(EXIT_FAILURE);
    }

    // 3. Communicate with client
    int num_client = 0;
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
        bytes_received = recvfrom(server_sock, buff, BUFF_SIZE - 1 , 0, ( struct sockaddr *)&client, &sin_size);
        if(bytes_received < 0){
            perror("\nError");
        }else{
            buff[bytes_received] = '\0';
            printf("ReceiveMsg from [%s:%d]:%s\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port), buff);
        }
        // printf("%s", buff);
        char msg[BUFF_SIZE];
        memset(msg, '\0', (strlen(msg)+ 1));

        if(is_valid_ip(buff)){
            inet_aton(buff, &ip_addr);
            host = gethostbyaddr(&ip_addr, sizeof(struct in_addr), AF_INET);
            if(host == NULL){
                sprintf(msg,"Not found information\n");
            }else{
                sprintf(msg, "Official IP: %s\nOfficial name: %s\n", inet_ntoa(*(struct in_addr*)host->h_addr_list[0]), host->h_name);
                if(host->h_aliases[0] != NULL){
                    strcat(msg, "Alias name: \n");
                    for(int i = 0; host->h_aliases[i]; i++){
                        strcat(msg, host->h_aliases[i]);
                        strcat(msg, "\n");
                    }
                }
            }
        }else{
            host = gethostbyname(buff);
            if(host == NULL){
                sprintf(msg,"Not found information\n");
            }else{
                sprintf(msg, "Official name: %s\n", host->h_name);
                for(int i = 0; host->h_aliases[i]; i++){
                    if(i == 0){
                        strcat(msg, "Alias name:\n");
                    }
                    strcat(msg, host->h_aliases[i]);
                }
                strcat(msg, "Official IP: ");
                strcat(msg, inet_ntoa(*(struct in_addr*)host->h_addr_list[0]));
                strcat(msg, "\n");
                for(int i = 1; host->h_addr_list[i]; i++){
                    if(i==1){
                        strcat(msg, "Alias IP:\n");
                    }
                    strcat(msg, inet_ntoa(*(struct in_addr*)host->h_addr_list[i]));
                    strcat(msg, "\n");
                }
            }
        }

        bytes_sent = sendto(server_sock, msg, strlen(msg), 0, (struct sockaddr *) &client, sin_size);
        if(bytes_sent < 0){
            perror("\nError: ");
            close(server_sock);
            exit(EXIT_FAILURE);
        }
    }
    
}
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<netdb.h>
#include<arpa/inet.h>
#define MAX_LIMIT 99999;

struct hostent *host;
struct hostent *test_host;
struct in_addr **addr_list;
struct in_addr ip_addr;

bool is_valid_ip(char *ip){
  struct in_addr ipv4_addr;
  return inet_pton(AF_INET, ip, &ipv4_addr) != 0;
}

int main()    
{
    int i;
    bool loop=true;
    char input_ip[99];
    while(1){
        printf("Input IP address or domain name: ");
        fgets(input_ip,sizeof(input_ip),stdin);

        input_ip[strcspn(input_ip, "\n")] = '\0';

        if(input_ip[0]=='\0'){
            printf("Goodbye!!!\n");
            break;
        }else{
            // printf("%d\n", strlen(input_ip));
            if(is_valid_ip(input_ip)){
                inet_aton(input_ip, &ip_addr);
                host = gethostbyaddr(&ip_addr, sizeof(struct in_addr), AF_INET);
                if(host==NULL){
                    printf("Not found information.\n\n");
                }else{
                    printf("Official IP: %s\n", inet_ntoa(*(struct in_addr*)host->h_addr_list[0]));
                    printf("Official name: %s\n", host->h_name);
                    if(host->h_aliases[0]!=NULL){
                        printf("Alias name:\n");
                        for(i=0; host->h_aliases[i]!=NULL;i++){
                            printf("%s\n", host->h_aliases[i]);
                        }
                    }
                    printf("\n");
                }
            }else{
                host = gethostbyname(input_ip);
                if(host==NULL){
                    printf("Not found information.\n\n");
                }else{
                    printf("Official name: %s\n", host->h_name);
                    for (int i = 0; host->h_aliases[i]; i++) {
                        if (i == 0) {
                            printf("Alias name:\n");
                        }
                        printf(" %s", host->h_aliases[i]);
                    }

                    printf("Official IP: %s\n", inet_ntoa(*(struct in_addr*)host->h_addr_list[0]));
                    for (int i = 1; host->h_addr_list[i]; i++) {
                        if (i == 1) {
                            printf("Alias IP:\n");
                        }
                        printf("%s\n", inet_ntoa(*(struct in_addr*)host->h_addr_list[i]));
                    }
                    printf("\n");
                }
            }
        }
    }
}
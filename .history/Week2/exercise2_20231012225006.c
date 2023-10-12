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

        // if (fgets(input_ip, sizeof(input_ip), stdin) == NULL) {
        //     printf("Error reading input.\n");
        //     return 1;
        // }
        input_ip[strcspn(input_ip, "\n")] = '\0';

        if(input_ip[0]=="\0"){
            printf("Goodbye!!!\n");
            break;
        }else{
            printf("%d\n", strlen(input_ip));
            if(is_valid_ip(input_ip)){
                inet_aton(input_ip, &ip_addr);
                host = gethostbyaddr(&ip_addr, sizeof(struct in_addr), AF_INET);
                if(host==NULL){
                    printf("Not found information.\n");
                }else{
                    printf("Official name: %s\n", host->h_name);
                    if(host->h_aliases[0]!=NULL){
                        printf("Alias name:\n");
                        for(i=0; host->h_aliases[i]!=NULL;i++){
                            printf("%s\n", host->h_aliases[i]);
                        }
                    }
                }
            }else{
                host = gethostbyname(input_ip);
                if(host==NULL){
                printf("Not found information.\n");
                }else{
                    addr_list = (struct in_addr **)host->h_addr_list;

                    printf("Official IP: %s\n", inet_ntoa(*addr_list[0]));
                    if(addr_list[1]!=NULL){
                        printf("Alias IP: \n");
                        for(i=1; addr_list[i]!=NULL;i++){
                        printf("%s\n", inet_ntoa(*addr_list[i]));
                        }
                    }
                }
            }
        }
    }
}
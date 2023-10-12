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
    char input_ip[99999];
    while(true){
        printf("Input IP address or domain name: ");
        fgets(input_ip, 99999, stdin);
        printf("%s",input_ip);
        if(input_ip=="\n"){
            break;
        }

        // if(input_ip=="" || input_ip==" "){
        //     loop=false;
        // }
        if(is_valid_ip(input_ip)){
            inet_aton(input_ip, &ip_addr);
            host = gethostbyaddr(&ip_addr, sizeof(struct in_addr), AF_INET);
            if(host==NULL){
                printf("Not found information");
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
            printf("Not found information.");
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
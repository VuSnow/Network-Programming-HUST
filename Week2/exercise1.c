#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<netdb.h>
#include<arpa/inet.h>

struct hostent *host;
struct hostent *test_host;
struct in_addr **addr_list;
struct in_addr ip_addr;

bool is_valid_ip(char *ip){
  struct in_addr ipv4_addr;
  return inet_pton(AF_INET, ip, &ipv4_addr) != 0;
}

int main(int argc, char *argv[])    
{
  if (argc != 2) {
    printf("Usage: %s <parameter>\n", argv[0]);
    return 1;
  }
  int i;
  if(is_valid_ip(argv[1])){
    inet_aton(argv[1], &ip_addr);
    host = gethostbyaddr(&ip_addr, sizeof(struct in_addr), AF_INET);
    if(host==NULL){
      printf("Not found information.\n");
    }else{
      printf("Official IP: %s\n", inet_ntoa(*(struct in_addr*)host->h_addr_list[0]));
      printf("Official name: %s\n", host->h_name);
      if(host->h_aliases[0]!=NULL){
        printf("Alias name:\n");
        for(i=0; host->h_aliases[i]!=NULL;i++){
          printf("%s\n", host->h_aliases[i]);
        }
      }
    }
  }else{
    host = gethostbyname(argv[1]);
    if(host==NULL){
      printf("Not found information.\n");
    }else{
      printf("Official name: %s\n", host->h_name);
      for (int i = 0; host->h_aliases[i]; i++) {
        if (i == 0) {
          printf("Alias name:\n");
        }
        printf("%s\n", host->h_aliases[i]);
      }

      printf("Official IP: %s\n", inet_ntoa(*(struct in_addr*)host->h_addr_list[0]));
      for (int i = 1; host->h_addr_list[i]; i++) {
        if (i == 1) {
          printf("Alias IP:\n");
        }
        printf("%s\n", inet_ntoa(*(struct in_addr*)host->h_addr_list[i]));
      }
    }
  }
}
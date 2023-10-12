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
  int i;
  if(is_valid_ip(argv[1])){
    inet_aton(argv[1], &ip_addr);
    host = gethostbyaddr(&ip_addr, sizeof(struct in_addr), AF_INET);
    // printf("%d", host==NULL);
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
    host = gethostbyname(argv[1]);
    test_host = getservbyname(argv[1]);
    printf("%d\n", test_host==NULL);
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
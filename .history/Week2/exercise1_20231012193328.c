#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<netdb.h>
#include<arpa/inet.h>

struct hostent *host;
struct in_addr **addr_list;
struct in_addr ip_addr;

bool is_valid_ip(char *ip){
  struct in_addr ipv4_addr;
  return inet_pton(AF_INET, ip, &ipv4_addr) != 0;
}

int main(int argc, char *argv[])    
{
  if(is_valid_ip(argv[1])){
    host = gethostbyaddr(&ip_addr, sizeof(struct in_addr), AF_INET);
    printf("%d", host==NULL);
    if(host==NULL){
      printf("Not found information");
    }
  }else{

  }
}
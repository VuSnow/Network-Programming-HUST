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

int main(int argc, const char *const argv[]){
  int i;
  for(i=0;i<argc;i++)
	{
		if(argv[i]!=NULL){
       			printf("%c \n",i,argv[i]);
		}
  }
}
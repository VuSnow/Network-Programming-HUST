#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netdb.h>
#include<arpa/inet.h>

struct hostent *host;
struct in_addr **addr_list;
struct in_addr ip_addr;

void getIpFromDomain(char domain[]){
  //check whether domain name exists
  if((host = gethostbyname(domain)) == NULL){
    herror("Not found IP address for domain name!");
    return;
  }
  
}
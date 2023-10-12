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


int is_valid_domain(const char *domain) {
    int len = strlen(domain);

    if (len < 3 || len > 255) {
        return 0; // Tên miền phải có ít nhất 3 ký tự và không quá 255 ký tự
    }

    for (int i = 0; i < len; i++) {
        if (!(isalnum(domain[i]) || domain[i] == '-' || domain[i] == '.')) {
            return 0; // Tên miền chỉ cho phép ký tự, số, dấu gạch ngang và dấu chấm
        }
    }

    if (domain[0] == '.' || domain[len - 1] == '.') {
        return 0; // Tên miền không thể bắt đầu hoặc kết thúc bằng dấu chấm
    }

    // Kiểm tra sự hiện diện của dấu chấm trung tâm
    if (strstr(domain, "..") != NULL) {
        return 0;
    }

    // Kiểm tra xem tên miền có chứa dấu chấm trung tâm không
    bool hasDot = false;
    for (int i = 0; i < len; i++) {
        if (domain[i] == '.') {
            hasDot = true;
            break;
        }
    }

    if (!hasDot) {
        return 0;
    }

    return 1;
}


int main(int argc, char *argv[])    
{
  int i;
  printf("%d\n", is_valid_domain(argv[1]));
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
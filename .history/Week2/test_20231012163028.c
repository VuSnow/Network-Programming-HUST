#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>

int is_valid_ip(const char *ip) {
    struct in_addr ipv4_addr;
    return inet_pton(AF_INET, ip, &ipv4_addr) != 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <parameter>\n", argv[0]);
        return 1;
    }
    printf("%d\n", is_valid_ip(argv[1]));

    struct hostent *host_info;
    struct in_addr ipv4_addr;
    const char *input = argv[1];

    // Check if the input is a valid IP address
    if (inet_pton(AF_INET, input, &ipv4_addr) != 0) {
        host_info = gethostbyaddr(&ipv4_addr, sizeof(struct in_addr), AF_INET);
        if (host_info == NULL) {
            printf("Invalid address or unable to resolve IP to domain.\n");
        } else {
            printf("Official domain name: %s\n", host_info->h_name);

            if (host_info->h_aliases[0] != NULL) {
                printf("Aliases:\n");
                for (int i = 0; host_info->h_aliases[i] != NULL; i++) {
                    printf("%s\n", host_info->h_aliases[i]);
                }
            }
        }
    } else {
        host_info = gethostbyname(input);
        if (host_info == NULL) {
            printf("Invalid address or unable to resolve domain to IP.\n");
        } else {
            printf("Official IP address: %s\n", inet_ntoa(*((struct in_addr *)host_info->h_addr_list[0])));

            if (host_info->h_addr_list[1] != NULL) {
                printf("Alias IP addresses:\n");
                for (int i = 1; host_info->h_addr_list[i] != NULL; i++) {
                    printf("%s\n", inet_ntoa(*((struct in_addr *)host_info->h_addr_list[i])));
                }
            }
        }
    }

    return 0;
}

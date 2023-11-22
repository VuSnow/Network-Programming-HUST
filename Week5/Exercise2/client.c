#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 5501
#define BUFF_SIZE 1024

void send_file(FILE *fp, int sockfd)
{
	char data[BUFF_SIZE];
	int bytes_sent, total_bytes = 0;
	while (fgets(data, BUFF_SIZE, fp) != NULL)
	{	
		bytes_sent = send(sockfd, data, sizeof(data), 0);
		total_bytes+= bytes_sent;
		if ( bytes_sent == -1)
		{
			perror("[-] Error in sending data");
			exit(1);
		}
		bzero(data, BUFF_SIZE);
	}

	printf("Total bytes sent: %d\n", total_bytes);
}

int main()
{
	int client_sock;
	char buff[BUFF_SIZE + 1];
	struct sockaddr_in server_addr; /* server's address information */
	int msg_len, bytes_sent, bytes_received;

	//Step 1: Construct socket
	client_sock = socket(AF_INET, SOCK_STREAM, 0);

	//Step 2: Specify server address
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);

	//Step 3: Request to connect server
	if (connect(client_sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) < 0)
	{
		printf("\nError!Can not connect to sever! Client exit imediately! ");
		return 0;
	}

	//Step 4: Communicate with server

	//send file
	FILE *fp;
	char *filename = (char*)malloc(100*sizeof(char));
	printf("[+] Enter file name: ");
	fgets(filename, BUFF_SIZE, stdin);
	filename[strcspn(filename, "\n")] = '\0';
	printf("%s\n",filename);
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		perror("[-]Error in reading file.");
		exit(1);
	}
	send_file(fp, client_sock);
	printf("[+] File data send successfully. \n");
	close(client_sock);
	printf("[+]Disconnected from the server. \n");

	//Step 4: Close socket
	close(client_sock);
	return 0;
}

#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>

#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 5500
#define BUFF_SIZE 1024

int main(){
	int client_sock;
	char buff[BUFF_SIZE + 1];
	struct sockaddr_in server_addr; /* server's address information */
	int msg_len, bytes_sent, bytes_received, total_bytes=0;
	bool exitLoop = false;
	//Step 1: Construct socket
	client_sock = socket(AF_INET,SOCK_STREAM,0);
	
	//Step 2: Specify server address
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
	
	//Step 3: Request to connect server
	if(connect(client_sock, (struct sockaddr*)&server_addr, sizeof(struct sockaddr)) < 0){
		printf("\nError!Can not connect to sever! Client exit imediately! ");
		return 0;
	}
		
	//Step 4: Communicate with server			
	do{
			printf("\nInsert string to send:");
			memset(buff,'\0',(strlen(buff)+1));
			fgets(buff, BUFF_SIZE, stdin);		

			if (buff[0] == 'q' || buff[0] == 'Q' ) {
				printf("Client close \n");
				exitLoop = true;
				//send message
				bytes_sent = send(client_sock, buff, msg_len, 0);
				total_bytes += bytes_sent;
				printf("Total bytes sent: %d\n", total_bytes);
				continue;
			}

			msg_len = strlen(buff);
			//send message
			bytes_sent = send(client_sock, buff, msg_len, 0);
			total_bytes += bytes_sent;
			if(bytes_sent < 0)
				perror("\nError: ");
			
			//receive echo reply
			bytes_received = recv(client_sock, buff, BUFF_SIZE, 0);
			if (bytes_received < 0)
					perror("\nError: ");
			else if (bytes_received == 0)
					printf("Connection closed.\n");
				
			buff[bytes_received] = '\0';
			printf("Reply from server: %s", buff);
	}while(!exitLoop);
	

	//Step 4: Close socket
	close(client_sock);
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/wait.h>
#include <errno.h>
#include <arpa/inet.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define PORT 5500
#define BUFF_SIZE 1024
#define BACKLOG 20

/* Handler process signal*/
void sig_child(int signo);

/*
* Receive and response message to client
*  sockfd: socket descriptor that connects to client 	
*/
void response(int sockfd);

int main(){
	
	int listen_sock, conn_sock; /* file descriptors */
	struct sockaddr_in server; /* server's address information */
	struct sockaddr_in client; /* client's address information */
	pid_t pid;
	int sin_size;

	if ((listen_sock=socket(AF_INET, SOCK_STREAM, 0)) == -1 ){  /* calls socket() */
		printf("socket() error\n");
		return 0;
	}
	
	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;         
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = htonl(INADDR_ANY);  /* INADDR_ANY puts your IP address automatically */   

	if(bind(listen_sock, (struct sockaddr*)&server, sizeof(server))==-1){ 
		perror("\nError: ");
		return 0;
	}     

	if(listen(listen_sock, BACKLOG) == -1){  
		perror("\nError: ");
		return 0;
	}
	
	/* Establish a signal handler to catch SIGCHLD */
	signal(SIGCHLD, sig_child);

	while(1){
		printf("new client\n");
		sin_size=sizeof(struct sockaddr_in);
		if ((conn_sock = accept(listen_sock, (struct sockaddr *)&client, &sin_size))==-1){
			if (errno == EINTR)
				continue;
			else{
				perror("\nError: ");			
				return 0;
			}
		}
		
		/* For each client, fork spawns a child, and the child handles the new client */
		pid = fork();
		
		/* fork() is called in child process */
		if(pid == 0){
			close(listen_sock);
			printf("You got a connection from %s\n", inet_ntoa(client.sin_addr)); /* prints client's IP */
			
			response(conn_sock);					
			exit(0);
		}
		
		/* The parent closes the connected socket since the child handles the new client */
		close(conn_sock);
	}
	close(listen_sock);
	return 0;
}

void sig_child(int signo){
	pid_t pid;
	int stat;
	
	/* Wait the child process terminate */
	while((pid = waitpid(-1, &stat, WNOHANG))>0)
		printf("\nClient %d terminated\n",pid);
}

void response(int sockfd) {

	char buff[BUFF_SIZE];
	char temp[1000];
	int bytes_sent, bytes_received;
	bool exitLoop = false;
	do{		
			bytes_received = recv(sockfd, buff, BUFF_SIZE, 0); //blocking
			if (buff[0] == 'q' || buff[0] == 'Q' ) {   //check user required to exit
            	exitLoop = true;
				continue;
        	}

			if (bytes_received < 0)
				perror("\nError: ");
			else if (bytes_received == 0)
				printf("Connection closed.");
			// to upper information of client 
			for(int i = 0;i < strlen(buff);i++)
			{
				temp[i] = toupper(buff[i]);
			}
			bytes_sent = send(sockfd, temp, bytes_received, 0); 
			if (bytes_sent < 0)
				perror("\nError: ");
	}while(!exitLoop);

			
	close(sockfd);
}

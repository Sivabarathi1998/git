#include<stdio.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{ 
 	char *ip="127.0.0.1";
  	int port=5555;
  	int n;

  	int socket_desc;
 	int client_sock;
  	int client_size;
  	struct sockaddr_in server_addr;
  	struct sockaddr_in client_addr;
  	char server_message[100];
  	char client_message[100];
  
  
  	// clean buffer 
  	memset(server_message,'\0',sizeof(server_message));
 	memset(client_message,'\0',sizeof(client_message));
  
  	// create TCP socket
  	socket_desc=socket(AF_INET,SOCK_STREAM,0);
  	if (socket_desc<0)
  	{ 
   		perror("[-]unable to establish a socket");
   		exit(1);
  	}
  	printf("\n[+] TCP socket connection created");

 	// assigning port and ip;
  	server_addr.sin_family=AF_INET;
  	server_addr.sin_port=htons(port);
  	server_addr.sin_addr.s_addr=inet_addr(ip);

  	//bind  port and ip
  	n =bind(socket_desc,(struct sockaddr*)&server_addr,sizeof(server_addr));
  	if(n<0)
  	{
   		perror("[-]unable to bind port and ip ");
   		exit(1);
  	}
  	printf("\n[+]sucessully binded the port and ip");

   	// Listen for clients:
    	if(listen(socket_desc, 1) < 0){ 
   	perror("[-]unable to listen ");
   	exit(1);
  	}
	printf("\nListening for incoming connections.....\n");


	//accept the client
  	client_size=sizeof(client_addr);
  	client_sock=accept(socket_desc,(struct sockaddr*)&client_addr,&client_size);
  	if(client_sock<0)
  	{
   		perror("[-] unable to accept a client ");
   		exit(1);
  	}
  	printf("\n[+]client connect at IP %s and port %d",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
        printf("\n[-----]type exit to quit the program\n");
 
  
	while(1)  
	{
   		//receive client message
   		if (recv(client_sock, client_message, sizeof(client_message), 0) < 0)
   		{
    			perror("[-] unable to recive a message from client ");
    			exit(1);
   		}
  
   		printf("\n[+]client_message:  %s",client_message);
   

   		//response from server
   		//strcpy(server_message, "Hello,This is the server.");   
   		printf("\n[+]server_message:   ");
   		gets(server_message);
   		if (send(client_sock, server_message, strlen(server_message), 0) < 0)
   		{
    			perror("[-] unable to respond a message to client ");
    			exit(1);
   		}
    		if(strcmp(server_message, "exit") == 0)
           	{
	     		goto close_label;
		}
 	}       //end of while loop

  
 	//closing client and socket connection
 	close_label:
 	{
 		close(client_sock);
 		close(socket_desc);
 		perror("[-] disconnected from server");
	}
	return 0;
}



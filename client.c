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

	int socket_desc;
	struct sockaddr_in server_addr;
	char server_message[100];
	char client_message[100];
  
  
 
	// Create TCP socket
	socket_desc=socket(AF_INET, SOCK_STREAM, 0);
	if (socket_desc<0)
	{ 
		perror("[-]unable to establish a socket");
		exit(1);
 	}
  	printf("\n[+] TCP socket connection created");

  	// Assigning port and ip;
  	server_addr.sin_family = AF_INET;
  	server_addr.sin_port = htons(port);
  	server_addr.sin_addr.s_addr = inet_addr(ip);
  
  	// Send connection request to server:
    	if(connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    	{
     		perror("[-]unable to establish a connection");
     		exit(1);
    	}
    	printf("\n[+]Connected with server successfully\n");
	printf("\n[------]type exit to quit the program\n");
   
  	while(1)
  	{
   		// clean buffer 
  		memset(server_message,'\0',sizeof(server_message));
  		memset(client_message,'\0',sizeof(client_message));

  		//sending message to server
  		printf("\n[+]client_message:   ");
  		gets(client_message);
  		if(send(socket_desc, client_message, strlen(client_message), 0) < 0)
  		{
   			perror("[-] unable to send message to server ");
   			exit(1);
 		}

  		if(strcmp(client_message, "exit") == 0)
          	{
	     		goto label;
		}

  

  		//receiving messages from server
  		if(recv(socket_desc,server_message,sizeof(server_message),0)<0)
  		{
   			perror("[-] unable to recive a message from server ");
   			exit(1);
  		}
  		printf("\n[+]server_message:   %s",server_message);
   
 
  
 	}      //end of while loop

	//closing client and socket connection
	label:
	{  
	close(socket_desc);
	perror("[-] disconnected from server");
	} 
  	return 0;
}

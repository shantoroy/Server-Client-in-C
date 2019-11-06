// Source: https://www.geeksforgeeks.org/socket-programming-cc/
// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 

int main(int argc, char const *argv[]) 
{ 
	int sock = 0, valread; 
	struct sockaddr_in serv_addr; 
	char recv_msg[1024] = {0};

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		printf("\n Socket creation error \n"); 
		return -1; 
	} 

    char hostname[20];
    int port_number;
    printf("Enter server host name: ");
    scanf("%s", hostname);
    printf("Enter server port number: ");
    scanf("%d", &port_number);

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_addr.s_addr = INADDR_ANY; 
	serv_addr.sin_port = htons(port_number);  

	inet_pton(AF_INET, hostname, &serv_addr.sin_addr);

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		printf("\nConnection Failed \n"); 
		return -1; 
	} 

    char email[50];
    printf("Enter the email address of a user:\n");
    scanf("%s", email);
	send(sock , email , strlen(email) , 0 ); 
	if(read( sock , recv_msg, 1024))
	{
		if(strcmp(recv_msg, "False")!=0)
		{
			printf("The public key of %s is:\n%s\n", email, recv_msg);
		}
		else
		{
			printf("The database had no public key for user %s\n", email);
		}
	}
	else
	{
		printf("Server Unavailable at the moment\n");
	}
    
	return 0;
} 

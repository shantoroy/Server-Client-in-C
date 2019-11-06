
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <fcntl.h>  

int main(int argc, char const *argv[]) 
{ 
	int server_fd, new_socket, valread; 
	struct sockaddr_in address; 
	int opt = 1, i = 0; 
	int addrlen = sizeof(address); 
	char recv_msg[1024] = {0}; 
    int port_number;
    char line[1000];
    char email[20], hex_key[40];
    char email_list[20][20], hex_key_list[20][80];

    // open the key file in read mode
    FILE *file = fopen("keys20.txt", "r");

    // Read line by line and get values
    while (fgets(line, sizeof line, file) != NULL)
    {
        // read formatted input from the file lines
        sscanf (line,"%s %s", email, hex_key);

        //copy emails and keys in separate lists
        strcpy(email_list[i], email);
        strcpy(hex_key_list[i], hex_key);
        i++;
    }

    fclose(file);           // closes the file

    int total = i+1;        // number of total items

    // Opt users for entering a port number
    printf("Enter server port number: ");
    scanf("%d", &port_number);
    
    // let's start the server with socket programming
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
    
    // Any address that is supported by internet protocol 
    address.sin_family = AF_INET;        

    // accept any type of address (hostname/IPv4/IPv6)     
    address.sin_addr.s_addr = INADDR_ANY;

    // convert integer values to network byte order
    address.sin_port = htons(port_number); 
    
    // Binding the port address with hostname or IP address
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) 
    { 
        perror("bind port with the address has been failed"); 
        exit(EXIT_FAILURE); 
    } 

    // listen for connection requests of clients
    if (listen(server_fd, 1) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 

    // Server will keep accepting connection requests until stopped forcefully
    while(1)
    {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
                        (socklen_t*)&addrlen))<0) 
        { 
            perror("Failed to accept a connection"); 
            exit(EXIT_FAILURE); 
        } 

        // for checking if server has the key
        int check = 0;          // 0-> not found, 1-> Found and break loop

        // read a new socket message of any size
        read( new_socket, recv_msg, sizeof(recv_msg)); 

        // print the request for a particular user
        printf("Received request for public key of %s\n",recv_msg ); 
        
        // loop to access server email list array
        for(i=0;i<total;i++)
        {
            // compare received message with email_list array items
            if (strcmp(email_list[i], recv_msg)==0)  
            {
                send(new_socket, hex_key_list[i], strlen(hex_key_list[i]), 0);
                check = 1;          // value update if success to find & send key
                break;
            }
        }

        // return False if the key is not found
        if(check==0)
        {
            char result[] = "False";
            send(new_socket, result, strlen(result), 0);
        }
    }

	return 0; 
} 

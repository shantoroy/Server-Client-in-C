# Request for public key of a user


## About
A server has a file containing RSA public keys for associated users. A client asks
for the key of a particular user by sending the associated email address to the server.
The server replies back with the key if he find corresponding entry, a False message 
otherwise. The server continues to accept new connections. The client exits with any
of the replies from a server.  

## Setup
No setup is required.


## Run server side
The server prompts for a port address. Enter any integer ranging from 1024-65535
and wait for a client to send message.

### Command
$ ./server

### Example scenario
Enter server port number: 2468
Received request for public key of fsuarez@uh.edu
Received request for public key of mleontov@uh.edu
Received request for public key of test@uh.edu


## Run client side
The client promts for hostname/IP address. If you are running in the same machine,
use `localhost` or `127.0.0.1`. Otherwise use the Name/IP address of another machine.
Then client prompts for port address. Use the same you used in the server. Then client
ask for user email address. Enter one from the `keys20.txt` file. You will receive the 
corresponding public key.  

### Command
$ ./client

### Example scenario - Server has the corresponding key
Enter server host name: localhost
Enter server port number: 2468
Enter the email address of a user:
fsuarez@uh.edu
The public key of fsuarez@uh.edu is:
0xfaeedR026974530159b1912579341fb731754695200000753671fff


### Example scenario - Server doesn't have the corresponding key
Enter server host name: localhost
Enter server port number: 2468
Enter the email address of a user:
test@uh.edu
The database had no public key for user test@uh.edu


### Example scenario - Server is not running
Enter server host name: localhost
Enter server port number: 2468
Connection Failed



## Thanks...
* [Stack Overflow](https://stackoverflow.com/)
* [Github](https://github.com)
* [GeeksforGeeks](https://www.geeksforgeeks.org)

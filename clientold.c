
#include "server450.h"
#include "util.h"

int main() {
	int clientSocket;
	int socket_fd;
	  struct addrinfo hints, *servinfo, *p;
		    struct sockaddr_storage their_addr; // connector's address information
		    socklen_t sin_size;

		    int yes=1;
		    char s[INET6_ADDRSTRLEN];
		    int rv;

		    memset(&hints, 0, sizeof hints);
		    hints.ai_family = AF_UNSPEC;
		    hints.ai_socktype = SOCK_STREAM;
		    hints.ai_flags = AI_PASSIVE; // use my IP

		    if ((rv = getaddrinfo(URL, CLIENTPORT, &hints, &servinfo)) != 0) {
		        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		        return 1;
		    }

		    // loop through all the results and bind to the first we can
		    for(p = servinfo; p != NULL; p = p->ai_next) {
		        if ((socket_fd = socket(p->ai_family, p->ai_socktype,
		                p->ai_protocol)) == -1) {
		            perror("server: socket");
		            continue;
		        }

		        if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes,
		                sizeof(int)) == -1) {
		            perror("setsockopt");
		            exit(1);
		        }

		        if (bind(socket_fd, p->ai_addr, p->ai_addrlen) == -1) {
		            close(socket_fd);
		            perror("server: bind");
		            continue;
		        }

		        break;
		    }


	/*---- Connect the socket to the server using the address struct ----*/

	if (connect(socket_fd, (struct sockaddr *) &server_addr, addrlen) < 0) {
		perror("Connect");
		exit(1);
	}


	/*---- Read the message from the server into the buffer ----*/
	if(recv(clientSocket, buffer, sizeof(buffer), 0)<0)
	{
		perror("receive");
		exit(1);
	}


	//server_info_node *obj=&buffer;
	/*---- Print the received message ----*/

	//buffer=obj;
	printf("Data received: %s\n",buffer);

	return 0;
}

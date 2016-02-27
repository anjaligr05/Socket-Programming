/****************************************EE 450 Socket Programming *******************************/
/**************************************Author: Anjali Gopal Reddy ********************************/

/*ServerC program*/

#include "util.h"

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa) {
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*) sa)->sin_addr);
	}
	return &(((struct sockaddr_in6*) sa)->sin6_addr);
}
int main() {

	int numbytes;
	char message_buffer[1026];

	/*The following socket functionality code is taken from Beej Guide*/
	int sockfd;
	struct addrinfo hints, *servinfo, *p;
	int rv;
	char s[INET6_ADDRSTRLEN];
	char s1[INET6_ADDRSTRLEN];

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	if ((rv = getaddrinfo(URL, CLIENTPORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;

	}

	printf("The server C is up and running\n");

	// loop through all the results and connect to the first we can
	for (p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol))
				== -1) {
			perror("ServerC: socket");
			continue;
		}
		if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("ServerC: connect");
			continue;
		}
		break;
	}
	if (p == NULL) {
		fprintf(stderr, "ServerC: failed to connect\n");
		return 2;
	}
	inet_ntop(p->ai_family, get_in_addr((struct sockaddr *) p->ai_addr), s,
			sizeof s);
	//printf("ServerC: connecting to %s\n", s);

	printf("The Server C has UDP port number %s and IP address %s\n",
					SERVER_C_PORT, s);

	freeaddrinfo(servinfo); // all done with this structure


	/*Server reads its neighbour information from a file*/
	FILE *file_ptr;


	file_ptr = fopen("serverC.txt", "r");
	if (file_ptr == NULL) {
		fprintf(stderr, "Cannot open file for reading!\n");
		perror("Error");
	}

	long lSize;
	char *buffer;
	fseek(file_ptr, 0, SEEK_END);
	lSize = ftell(file_ptr);
	rewind(file_ptr);

	/* Copy the file text into a buffer*/

	buffer=malloc((size_t)file_ptr+1);
	if (!buffer){
		fclose(file_ptr);
		fprintf(stderr,"Memory allocation failed!\n");
		exit(1);
	}

	if (1 != fread(buffer, lSize, 1, file_ptr)){
		fclose(file_ptr);
		free(buffer);
		fprintf(stderr,"File read failed!\n");
		exit(1);
	}

	printf("The Server C has the following neighbor information:\n");
			printf("Neighbor------Cost\n");
		printf("%s\n",buffer);

	strcpy(message_buffer,buffer);
	fclose(file_ptr);
	free(buffer);

	strcat(message_buffer,"End of file :C");
	if ((numbytes = send(sockfd, message_buffer, strlen(message_buffer), 0)) == -1) {
		perror("send");
		exit(1);
	}
	struct sockaddr_in addr_tcp;
		socklen_t addr_tcp_len;
		getsockname(sockfd,(struct sockaddr *)&addr_tcp,&addr_tcp_len);
		printf("The Server C finishes sending its neighbor information to the Client with TCP port number %s and IP address %s \n(Client’s TCP port number and IP address).\n",CLIENTPORT,s);

		printf("For this connection with the Client, the Server C has TCP port number %d and IP address %s.\n",htons(addr_tcp.sin_port),s);


	close(sockfd);

	/*UDP Socket*/
			int sockfd_udp;
			struct addrinfo hints_udp, *servinfo_udp, *p_udp;
			int rv_udp;
			int numbytes_udp;
			struct sockaddr_in their_addr_udp;
			struct sockaddr_in;
			char buf_udp[MAXLENGTH];
			socklen_t addr_len_udp;
			char s_udp[INET6_ADDRSTRLEN];

			memset(&hints_udp, 0, sizeof hints_udp);
			hints_udp.ai_family = AF_UNSPEC; // set to AF_INET to force IPv4
			hints_udp.ai_socktype = SOCK_DGRAM;
			hints_udp.ai_flags = AI_PASSIVE; // use my IP

			if ((rv_udp = getaddrinfo(NULL, SERVER_C_PORT, &hints_udp,
					&servinfo_udp)) != 0) {
				fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv_udp));
				return 1;
			}

			// loop through all the results and bind to the first we can
			for (p_udp = servinfo_udp; p_udp != NULL; p_udp = p_udp->ai_next) {
				if ((sockfd_udp = socket(p_udp->ai_family, p_udp->ai_socktype,
						p_udp->ai_protocol)) == -1) {
					perror("ServerB: socket");
					continue;
				}

				if (bind(sockfd_udp, p_udp->ai_addr, p_udp->ai_addrlen) == -1) {
					close(sockfd_udp);
					perror("ServerC: bind");
					continue;
				}

				break;
			}

			if (p_udp == NULL) {
				fprintf(stderr, "ServerC: failed to bind socket\n");
				return 2;
			}

			inet_ntop(p_udp->ai_family, get_in_addr((struct sockaddr *) p_udp->ai_addr), s_udp,
							sizeof s_udp);
			freeaddrinfo(servinfo_udp);

			//printf("ServerC: waiting to recvfrom...\n");

			addr_len_udp = sizeof their_addr_udp;
			if ((numbytes_udp = recvfrom(sockfd_udp, buf_udp, MAXLENGTH - 1, 0,
					(struct sockaddr *) &their_addr_udp, &addr_len_udp)) == -1) {
				perror("recvfrom");
				exit(1);
			}



			printf("\nThe server C has received the network topology from the Client with UDP port number %d and IP address %s\n(Client’s UDP port number and IP address) as follows:\n",ntohs(their_addr_udp.sin_port),s);
				printf("Edge------Cost\n");

			/*printf("SeverC: got packet from %s\n",
					inet_ntop(their_addr_udp.ss_family,
							get_in_addr((struct sockaddr *) &their_addr_udp), s_udp,
							sizeof s_udp));*/
			//printf("ServerC: packet is %d bytes long\n", numbytes_udp);
			buf_udp[numbytes_udp] = '\0';
			//printf("ServerC: packet contains \"%s\"\n", buf_udp);
			printf("%s\n",buf_udp);

				printf("For this connection with Client, The Server C has UDP port number %s and IP address %s.\n",SERVER_C_PORT,s);
			close(sockfd_udp);



	return 0;
}

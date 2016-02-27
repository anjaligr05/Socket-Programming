/****************************************EE 450 Socket Programming *******************************/
/**************************************Author: Anjali Gopal Reddy ********************************/

/*Server program*/

#include "server450.h"
#include "util.h"

/* The following code has been taken from Beej guide */
void sigchld_handler(int s) {
	// waitpid() might overwrite errno, so we save and restore it:
	int saved_errno = errno;
	printf("Entered in handler");
	while (waitpid(-1, NULL, WNOHANG) > 0)
		;

	errno = saved_errno;
}

server_list_obj* append_server(server_info_node *ptr, server_list_obj *head) {

	server_list_obj *temp, *right;
	temp = (server_list_obj*) malloc(sizeof(server_list_obj));
	temp->obj = (server_info_node*) malloc(sizeof(server_info_node));
	strcpy(temp->obj->server_name, ptr->server_name);
	temp->obj->cost = ptr->cost;
	if (head == NULL) {

		head = (server_list_obj*) malloc(sizeof(server_list_obj));
		head->obj = (server_info_node*) malloc(sizeof(server_info_node));
		strcpy(head->obj->server_name, ptr->server_name);
		head->obj->cost = ptr->cost;
		head->next = NULL;
		return head;
	} else {

		right = head;
		while (right->next != NULL)
			right = right->next;
		right->next = temp;
		right = temp;
		head->num_servers++;
		right->next = NULL;
		return right;
	}

}

void store_in_serverA(void * buffer, int (*adjacency_matrix)[4]) {

	/*Parse the data at the Client side and store in a data structure*/
	server_info_node *server_info_ptr = (server_info_node*) malloc(
			sizeof(server_info_node));
	server_list_obj *head = (server_list_obj*) malloc(sizeof(server_list_obj));
	head = NULL;

	char local_buf[MAXLENGTH];
	strncpy(local_buf, buffer, strlen(buffer) + 1);

	char * new_buf = strtok(local_buf, "\n");
	int first = 0;
	while (new_buf != NULL) {

		if (strcmp(new_buf, "End of file :A") != 0) {

			sscanf(new_buf, "%s\t%d", server_info_ptr->server_name,
					&server_info_ptr->cost);
			if (first == 0) {
				head = append_server(server_info_ptr, head);
			} else {
				append_server(server_info_ptr, head);
			}
			new_buf = strtok(NULL, "\n");
			first++;
		} else {
			new_buf = strtok(NULL, "\n");

		}

	}

	printf("The Server A has the following neighbor information:\n");
	printf("Neighbor------Cost\n");
	server_list_obj * next1 = malloc(sizeof(server_list_obj));
	next1 = head;
	while (next1 != NULL) {

		printf("%s\t\t%d\n", next1->obj->server_name, next1->obj->cost);
		next1 = next1->next;
	}
	free(next1);

	int i = 0;
	int j = 0;
	server_list_obj * next = malloc(sizeof(server_list_obj));

	for (j = 0; j < 4; j++) {
		if (i == j) {

			adjacency_matrix[i][j] = 0;

		} else if (j == 1) {
			next = head;
			while (next != NULL) {

				if (strcmp(next->obj->server_name, "serverB") == 0) {
					adjacency_matrix[i][j] = next->obj->cost;
				}
				next = next->next;
			}
			free(next);

		} else if (j == 2) {
			next = head;
			while (next != NULL) {

				if (strcmp(next->obj->server_name, "serverC") == 0) {
					adjacency_matrix[i][j] = next->obj->cost;
				}
				next = next->next;
			}
			free(next);

		} else if (j == 3) {
			next = head;
			while (next != NULL) {

				if (strcmp(next->obj->server_name, "serverD") == 0) {
					adjacency_matrix[i][j] = next->obj->cost;
				}
				next = next->next;
			}
			free(next);

		}
	}

	free(head);
	free(server_info_ptr);

}
void store_in_serverB(void * buffer, int (*adjacency_matrix)[4]) {

	/*Parse the data at the Client side and store in a data structure*/
	server_info_node *server_info_ptr = (server_info_node*) malloc(
			sizeof(server_info_node));
	server_list_obj *head = NULL;

	char local_buf[MAXLENGTH];
	strncpy(local_buf, buffer, strlen(buffer) + 1);

	char * new_buf = strtok(local_buf, "\n");

	int first = 0;
	while (new_buf != NULL) {

		if (strcmp(new_buf, "End of file :B") != 0) {

			sscanf(new_buf, "%s\t%d", server_info_ptr->server_name,
					&server_info_ptr->cost);
			if (first == 0) {
				head = append_server(server_info_ptr, head);
			} else {
				append_server(server_info_ptr, head);
			}
			new_buf = strtok(NULL, "\n");
			first++;
		} else {
			new_buf = strtok(NULL, "\n");

		}

	}

	printf("The Server B has the following neighbor information:\n");
	printf("Neighbor------Cost\n");
	server_list_obj * next1 = malloc(sizeof(server_list_obj));
	next1 = head;
	while (next1 != NULL) {

		printf("%s\t\t%d\n", next1->obj->server_name, next1->obj->cost);
		next1 = next1->next;
	}
	free(next1);

	int i = 1;
	int j = 0;
	server_list_obj * next = malloc(sizeof(server_list_obj));

	for (j = 0; j < 4; j++) {
		if (i == j) {
			adjacency_matrix[i][j] = 0;
		} else if (j == 0) {
			next = head;
			while (next != NULL) {

				if (strcmp(next->obj->server_name, "serverA") == 0) {
					adjacency_matrix[i][j] = next->obj->cost;
				}
				next = next->next;
			}
			free(next);

		} else if (j == 2) {
			next = head;
			while (next != NULL) {

				if (strcmp(next->obj->server_name, "serverC") == 0) {
					adjacency_matrix[i][j] = next->obj->cost;
				}
				next = next->next;
			}
			free(next);

		} else if (j == 3) {
			next = head;
			while (next != NULL) {

				if (strcmp(next->obj->server_name, "serverD") == 0) {
					adjacency_matrix[i][j] = next->obj->cost;
				}
				next = next->next;
			}
			free(next);

		}
	}

	free(head);
	free(server_info_ptr);

}
void store_in_serverC(void * buffer, int (*adjacency_matrix)[4]) {

	/*Parse the data at the Client side and store in a data structure*/
	server_info_node *server_info_ptr = (server_info_node*) malloc(
			sizeof(server_info_node));
	server_list_obj *head = NULL;

	char * new_buf = strtok(buffer, "\n");

	int first = 0;
	while (new_buf != NULL) {

		if (strcmp(new_buf, "End of file :C") != 0) {

			sscanf(new_buf, "%s\t%d", server_info_ptr->server_name,
					&server_info_ptr->cost);
			if (first == 0) {
				head = append_server(server_info_ptr, head);
			} else {
				append_server(server_info_ptr, head);
			}
			new_buf = strtok(NULL, "\n");
			first++;
		} else {
			new_buf = strtok(NULL, "\n");

		}

	}

	printf("The Server C has the following neighbor information:\n");
	printf("Neighbor------Cost\n");
	server_list_obj * next1 = malloc(sizeof(server_list_obj));
	next1 = head;
	while (next1 != NULL) {

		printf("%s\t\t%d\n", next1->obj->server_name, next1->obj->cost);
		next1 = next1->next;
	}
	free(next1);

	int i = 2;
	int j = 0;
	server_list_obj * next = malloc(sizeof(server_list_obj));

	for (j = 0; j < 4; j++) {
		if (i == j) {
			adjacency_matrix[i][j] = 0;
		} else if (j == 0) {
			next = head;
			while (next != NULL) {

				if (strcmp(next->obj->server_name, "serverA") == 0) {
					adjacency_matrix[i][j] = next->obj->cost;
				}
				next = next->next;
			}
			free(next);

		} else if (j == 1) {
			next = head;
			while (next != NULL) {

				if (strcmp(next->obj->server_name, "serverB") == 0) {
					adjacency_matrix[i][j] = next->obj->cost;
				}
				next = next->next;
			}
			free(next);

		} else if (j == 3) {
			next = head;
			while (next != NULL) {

				if (strcmp(next->obj->server_name, "serverD") == 0) {
					adjacency_matrix[i][j] = next->obj->cost;
				}
				next = next->next;
			}
			free(next);

		}
	}

	free(next);
	free(head);
	free(server_info_ptr);
}
void store_in_serverD(void * buffer, int (*adjacency_matrix)[4]) {

	/*Parse the data at the Client side and store in a data structure*/
	server_info_node *server_info_ptr = (server_info_node*) malloc(
			sizeof(server_info_node));
	server_list_obj *head = NULL;

	char * new_buf = strtok(buffer, "\n");

	int first = 0;
	while (new_buf != NULL) {

		if (strcmp(new_buf, "End of file :D") != 0) {

			sscanf(new_buf, "%s\t%d", server_info_ptr->server_name,
					&server_info_ptr->cost);
			if (first == 0) {
				head = append_server(server_info_ptr, head);
			} else {
				append_server(server_info_ptr, head);
			}
			new_buf = strtok(NULL, "\n");
			first++;
		} else {
			new_buf = strtok(NULL, "\n");

		}

	}

	printf("The Server D has the following neighbor information:\n");
	printf("Neighbor------Cost\n");
	server_list_obj * next1 = malloc(sizeof(server_list_obj));
	next1 = head;
	while (next1 != NULL) {

		printf("%s\t\t%d\n", next1->obj->server_name, next1->obj->cost);
		next1 = next1->next;
	}
	free(next1);

	int i = 3;
	int j = 0;
	server_list_obj * next = malloc(sizeof(server_list_obj));

	for (j = 0; j < 4; j++) {
		if (i == j) {
			adjacency_matrix[i][j] = 0;
		} else if (j == 0) {
			next = head;
			while (next != NULL) {

				if (strcmp(next->obj->server_name, "serverA") == 0) {
					adjacency_matrix[i][j] = next->obj->cost;
				}
				next = next->next;
			}
			free(next);

		} else if (j == 1) {
			next = head;
			while (next != NULL) {

				if (strcmp(next->obj->server_name, "serverB") == 0) {
					adjacency_matrix[i][j] = next->obj->cost;
				}
				next = next->next;
			}
			free(next);

		} else if (j == 2) {
			next = head;
			while (next != NULL) {

				if (strcmp(next->obj->server_name, "serverC") == 0) {
					adjacency_matrix[i][j] = next->obj->cost;
				}
				next = next->next;
			}
			free(next);

		}
	}

	free(next);
	free(head);
	free(server_info_ptr);
}

/***Broadcast the network topology to A****/
int broadcast_topology_A(void *buffer, char s1[INET6_ADDRSTRLEN],
		char s[INET6_ADDRSTRLEN]) {

	/*Broadcast network topology to each server*/
	/*UDP Connection*/

	int sockfd;
	struct addrinfo hints, *servinfo, *p;
	int rv;
	int numbytes;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

	if ((rv = getaddrinfo(URL, SERVER_A_PORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return -1;
	}
	// loop through all the results and make a socket
	for (p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol))
				== -1) {
			perror("Client: socket");
			continue;
		}

		break;
	}

	if (p == NULL) {
		fprintf(stderr, "Client: failed to create socket\n");
		return 2;
	}

	if ((numbytes = sendto(sockfd, buffer, strlen(buffer), 0, p->ai_addr,
			p->ai_addrlen)) == -1) {
		perror("Client: sendto");
		exit(1);
	}

	struct sockaddr_in addr;
	socklen_t addr_len = sizeof(addr);
	getsockname(sockfd, (struct sockaddr*) &addr, &addr_len);
	printf(
			"\nThe Client has sent the network topology to the Server A with UDP port number %s and IP address %s\n(Server A’s UDP port number and IP address) as follows:\n",
			SERVER_A_PORT, s1);
	printf("Edge------Cost\n");
	printf("%s\n", (char *) buffer);

	printf(
			"For this connection with Server A, The Client has UDP port number %d and IP address %s.\n",
			htons(addr.sin_port), s);
	freeaddrinfo(servinfo);

//	printf("Client: sent %d bytes to %s\n", numbytes, SERVER_A_PORT);
	close(sockfd);
	return 0;
}

/***Broadcast the network topology to A****/
int broadcast_topology_B(void *buffer, char s1[INET6_ADDRSTRLEN],
		char s[INET6_ADDRSTRLEN]) {

	/*Broadcast network topology to each server*/
	/*UDP Connection*/

	int sockfd;
	struct addrinfo hints, *servinfo, *p;
	int rv;
	int numbytes;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

	if ((rv = getaddrinfo(URL, SERVER_B_PORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return -1;
	}
	// loop through all the results and make a socket
	for (p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol))
				== -1) {
			perror("Client: socket");
			continue;
		}

		break;
	}

	if (p == NULL) {
		fprintf(stderr, "Client: failed to create socket\n");
		return 2;
	}

	if ((numbytes = sendto(sockfd, buffer, strlen(buffer), 0, p->ai_addr,
			p->ai_addrlen)) == -1) {
		perror("Client: sendto");
		exit(1);
	}
	struct sockaddr_in addr;
	socklen_t addr_len = sizeof(addr);
	getsockname(sockfd, (struct sockaddr*) &addr, &addr_len);
	printf(
			"The Client has sent the network topology to the Server B with UDP port number %s and IP address %s\n(Server B’s UDP port number and IP address) as follows:\n",
			SERVER_B_PORT, s1);
	printf("Edge------Cost\n");
	printf("%s\n", (char *) buffer);
	printf(
			"For this connection with Server B, The Client has UDP port number %d and IP address %s.\n",
			htons(addr.sin_port), s);

	freeaddrinfo(servinfo);

//	printf("Client: sent %d bytes to %s\n", numbytes, SERVER_B_PORT);
	close(sockfd);
	return 0;
}

/***Broadcast the network topology to C****/
int broadcast_topology_C(void *buffer, char s1[INET6_ADDRSTRLEN],
		char s[INET6_ADDRSTRLEN]) {

	/*Broadcast network topology to each server*/
	/*UDP Connection*/

	int sockfd;
	struct addrinfo hints, *servinfo, *p;
	int rv;
	int numbytes;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

	if ((rv = getaddrinfo(URL, SERVER_C_PORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return -1;
	}
	// loop through all the results and make a socket
	for (p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol))
				== -1) {
			perror("Client: socket");
			continue;
		}

		break;
	}

	if (p == NULL) {
		fprintf(stderr, "Client: failed to create socket\n");
		return 2;
	}

	if ((numbytes = sendto(sockfd, buffer, strlen(buffer), 0, p->ai_addr,
			p->ai_addrlen)) == -1) {
		perror("Client: sendto");
		exit(1);
	}

	struct sockaddr_in addr;
	socklen_t addr_len = sizeof(addr);
	getsockname(sockfd, (struct sockaddr*) &addr, &addr_len);
	printf(
			"The Client has sent the network topology to the network topology to the Server C with UDP port number %s and IP address %s\n(Server C’s UDP port number and IP address) as follows:\n",
			SERVER_C_PORT, s1);
	printf("Edge------Cost\n");
	printf("%s\n", (char *) buffer);
	printf(
			"For this connection with Server C, The Client has UDP port number %d and IP address %s.\n",
			htons(addr.sin_port), s);

	freeaddrinfo(servinfo);

//	printf("Client: sent %d bytes to %s\n", numbytes, SERVER_C_PORT);
	close(sockfd);
	return 0;
}

/***Broadcast the network topology to D****/
int broadcast_topology_D(void *buffer, char s1[INET6_ADDRSTRLEN],
		char s[INET6_ADDRSTRLEN]) {

	/*Broadcast network topology to each server*/
	/*UDP Connection*/

	int sockfd;
	struct addrinfo hints, *servinfo, *p;
	int rv;
	int numbytes;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

	if ((rv = getaddrinfo(URL, SERVER_D_PORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return -1;
	}
	// loop through all the results and make a socket
	for (p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol))
				== -1) {
			perror("Client: socket");
			continue;
		}

		break;
	}

	usleep(10000);
	if (p == NULL) {
		fprintf(stderr, "Client: failed to create socket\n");
		return 2;
	}

	if ((numbytes = sendto(sockfd, buffer, strlen(buffer), 0, p->ai_addr,
			p->ai_addrlen)) == -1) {
		perror("Client: sendto");
		exit(1);
	}

	struct sockaddr_in addr;
	socklen_t addr_len = sizeof(addr);
	getsockname(sockfd, (struct sockaddr*) &addr, &addr_len);
	printf(
			"The Client has sent the network topology to the network topology to the Server D with UDP port number %s and IP address %s\n(Server D’s UDP port number and IP address) as follows:\n",
			SERVER_D_PORT, s1);
	printf("Edge------Cost\n");
	printf("%s\n", (char *) buffer);

	printf(
			"For this connection with Server D, The Client has UDP port number %d and IP address %s.\n",
			htons(addr.sin_port), s);
	freeaddrinfo(servinfo);

//	printf("Client: sent %d bytes to %s\n", numbytes, SERVER_D_PORT);
	close(sockfd);
	return 0;
}
// A utility function to find the vertex with minimum key value, from
// the set of vertices not yet included in MST
int minKey(int key[], bool mstSet[]) {
	// Initialize min value
	int min = INT_MAX, min_index;
	int v;
	for (v = 0; v < 4; v++)
		if (mstSet[v] == false && key[v] < min)
			min = key[v], min_index = v;

	return min_index;
}

int print_MST(int parent[], int n, int (*adjacency_matrix)[4]) {

	int sum = 0;

	int i;
	for (i = 1; i < 4; i++) {
		sum += adjacency_matrix[i][parent[i]];

	}
	printf("\nThe Client has calculated a tree. The tree cost is %d.\n", sum);
	printf("Edge   Cost\n");
	int j;
	for (j = 1; j < 4; j++) {
		if (parent[j] == 0) {
			if (j == 1)
				printf("AB    %d \n", adjacency_matrix[j][parent[j]]);
			else if (j == 2)
				printf("AC    %d \n", adjacency_matrix[j][parent[j]]);
			else if (j == 3)
				printf("AD    %d \n", adjacency_matrix[j][parent[j]]);
		} else if (parent[j] == 1) {
			if (j == 2) {
				printf("BC    %d \n", adjacency_matrix[j][parent[j]]);
			} else if (j == 3) {
				printf("BD    %d \n", adjacency_matrix[j][parent[j]]);

			}

		} else if (parent[j] == 2) {
			if (j == 3)
				printf("CD    %d \n", adjacency_matrix[j][parent[j]]);
		}

	}
	return 0;
}

/*The following algorithm has been adopted from the internet to calculate Mininmum Spannning Tree using Prim's Algorithm*/
void prim_MST_algo(int (*adjacency_matrix)[4]) {
	int initial[4];
	int key_value[4];
	bool minimum_span_set[4];

	int i = 0;
	for (i = 0; i < 4; i++)
		key_value[i] = INT_MAX, minimum_span_set[i] = false;

	key_value[0] = 0;
	initial[0] = -1;

	int count = 0;
	for (count = 0; count < 4 - 1; count++) {

		int u = minKey(key_value, minimum_span_set);

		minimum_span_set[u] = true;

		int v;
		for (v = 0; v < 4; v++)

			if (adjacency_matrix[u][v] && minimum_span_set[v] == false
					&& adjacency_matrix[u][v] < key_value[v])
				initial[v] = u, key_value[v] = adjacency_matrix[u][v];
	}

	print_MST(initial, 4, adjacency_matrix);
}

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa) {
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*) sa)->sin_addr);
	}
	return &(((struct sockaddr_in6*) sa)->sin6_addr);
}

int main(void) {

	/*Shared gloabal variables*/

	flagA = mmap(NULL, sizeof *flagA, PROT_READ | PROT_WRITE,
	MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*flagA = 0;

	flagB = mmap(NULL, sizeof *flagB, PROT_READ | PROT_WRITE,
	MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*flagB = 0;

	flagC = mmap(NULL, sizeof *flagC, PROT_READ | PROT_WRITE,
	MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*flagC = 0;

	flagD = mmap(NULL, sizeof *flagD, PROT_READ | PROT_WRITE,
	MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*flagD = 0;

	int (*adjacency_matrix)[4] = (int (*)[4]) mmap(NULL, sizeof(int) * 4 * 4,
	PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

	int sockfd, new_fd; // listen on sock_fd, new connection on new_fd
	struct addrinfo hints, *servinfo, *p;
	struct sockaddr_storage their_addr; // connector's address information

	socklen_t sin_size;

	char send_buffer[MAXLENGTH];
	int yes = 1;
	char buf[MAXLENGTH];
	int numbytes;
	char s[INET6_ADDRSTRLEN];
	char s1[INET6_ADDRSTRLEN];
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
	for (p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol))
				== -1) {
			perror("client: socket");
			continue;
		}
		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))
				== -1) {
			perror("setsockopt");
			exit(1);
		}
		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("client: bind");
			continue;
		}
		break;
	}

	freeaddrinfo(servinfo); //all done with this structure

	if (p == NULL) {
		fprintf(stderr, "client: failed to bind\n");
		exit(1);
	}

	if (listen(sockfd, BACKLOG) == -1) {
		perror("listen");
		exit(1);
	}

	inet_ntop(p->ai_family, get_in_addr((struct sockaddr *) p->ai_addr), s,
			sizeof s);
	printf("The Client has TCP port number %s and IP address %s.\n", CLIENTPORT,
			s);

	//printf("client: waiting for connections...\n");

	while (1) { // main accept() loop
		sin_size = sizeof their_addr;

		new_fd = accept(sockfd, (struct sockaddr *) &their_addr, &sin_size);
		if (new_fd == -1) {
			perror("accept");
			continue;
			//break;
		}

		inet_ntop(their_addr.ss_family,
				get_in_addr((struct sockaddr *) &their_addr), s1, sizeof s1);

		//	printf("client: got connection from %s\n", s);

		if (!fork()) { // this is the child process
			//	close(sockfd);
			if ((numbytes = recv(new_fd, buf, MAXLENGTH - 1, 0)) == -1) {
				perror("recv");
				close(new_fd);
				exit(1);
			}

			buf[numbytes] = '\0';
			char* tempstr = malloc(sizeof(buf));
			strncpy(tempstr, buf, numbytes + 1);

			char *new_buf1;

			new_buf1 = strtok(tempstr, "\n");

			while (new_buf1 != NULL) {

				if (strncmp(new_buf1, "End of file :A",
						strlen("End of file :A")) == 0) {
					*flagA = 1;

					struct sockaddr_in addr_tcp;
					socklen_t addr_len_tcp = sizeof(addr_tcp);
					getpeername(new_fd, (struct sockaddr*) &addr_tcp,
							&addr_len_tcp);

					printf(
							"The Client receivers neighbor information from the ServerA with TCP port number %d and IP address %s\n(The Server A’s TCP port number and IP address).\n",
							ntohs(addr_tcp.sin_port), s);
					store_in_serverA(buf, adjacency_matrix);

					printf(
							"For this connection with Server A, The Client has TCP port number %s and IP address %s.\n",
							CLIENTPORT, s);

				} else if (strncmp(new_buf1, "End of file :B",
						strlen("End of file :B")) == 0) {
					*flagB = 1;

					struct sockaddr_in addr;
					socklen_t addr_len = sizeof(addr);
					getpeername(new_fd, (struct sockaddr*) &addr, &addr_len);

					printf(
							"The Client receivers neighbor information from the ServerB with TCP port number %d and IP address %s\n(The Server B’s TCP port number and IP address).\n",
							htons(addr.sin_port), s);
					store_in_serverB(buf, adjacency_matrix);
					printf(
							"For this connection with Server B, The Client has TCP port number %s and IP address %s.\n",
							CLIENTPORT, s);

				} else if (strncmp(new_buf1, "End of file :C",
						strlen("End of file :C")) == 0) {
					*flagC = 1;

					struct sockaddr_in addr;
					socklen_t addr_len = sizeof(addr);
					getpeername(new_fd, (struct sockaddr*) &addr, &addr_len);
					printf(
							"The Client receivers neighbor information from the ServerC with TCP port number %d and IP address %s\n(The Server C’s TCP port number and IP address).\n",
							htons(addr.sin_port), s);
					store_in_serverC(buf, adjacency_matrix);
					printf(
							"For this connection with Server C, The Client has TCP port number %s and IP address %s.\n",
							CLIENTPORT, s);

				} else if (strncmp(new_buf1, "End of file :D",
						strlen("End of file :D")) == 0) {
					*flagD = 1;

					struct sockaddr_in addr;
					socklen_t addr_len = sizeof(addr);
					getpeername(new_fd, (struct sockaddr*) &addr, &addr_len);

					printf(
							"The Client receivers neighbor information from the ServerD with TCP port number %d and IP address %s\n(The Server D’s TCP port number and IP address).\n",
							htons(addr.sin_port), s);

					store_in_serverD(buf, adjacency_matrix);
					printf(
							"For this connection with Server D, The Client has TCP port number %s and IP address %s.\n",
							CLIENTPORT, s);

				}
				new_buf1 = strtok(NULL, "\n");

			}

			if (*flagA == 1 && *flagB == 1 && *flagC == 1 && *flagD == 1) {

				close(new_fd);

			}

		}

		close(new_fd);

		if (*flagA == 1 && *flagB == 1 && *flagC == 1 && *flagD == 1) {

			sprintf(send_buffer,
					"%d\t%d\t%d\t%d\n%d\t%d\t%d\t%d\n%d\t%d\t%d\t%d\n%d\t%d\t%d\t%d\n",
					adjacency_matrix[0][0], adjacency_matrix[0][1],
					adjacency_matrix[0][2], adjacency_matrix[0][3],
					adjacency_matrix[1][0], adjacency_matrix[1][1],
					adjacency_matrix[1][2], adjacency_matrix[1][3],
					adjacency_matrix[2][0], adjacency_matrix[2][1],
					adjacency_matrix[2][2], adjacency_matrix[2][3],
					adjacency_matrix[3][0], adjacency_matrix[3][1],
					adjacency_matrix[3][2], adjacency_matrix[3][3]);

			char send_buffer2[MAXLENGTH] = "";
			char send_buffer3[MAXLENGTH] = "";
			if (adjacency_matrix[0][1] != 0) {
				sprintf(send_buffer2, "AB\t%d\n", adjacency_matrix[0][1]);
				strcat(send_buffer3, send_buffer2);
			}
			if (adjacency_matrix[0][2] != 0) {
				sprintf(send_buffer2, "AC\t%d\n", adjacency_matrix[0][2]);
				strcat(send_buffer3, send_buffer2);
			}
			if (adjacency_matrix[0][3] != 0) {
				sprintf(send_buffer2, "AD\t%d\n", adjacency_matrix[0][3]);
				strcat(send_buffer3, send_buffer2);
			}
			if (adjacency_matrix[1][2] != 0) {
				sprintf(send_buffer2, "BC\t%d\n", adjacency_matrix[1][2]);
				strcat(send_buffer3, send_buffer2);
			}
			if (adjacency_matrix[1][3] != 0) {
				sprintf(send_buffer2, "BD\t%d\n", adjacency_matrix[1][3]);
				strcat(send_buffer3, send_buffer2);
			}
			if (adjacency_matrix[2][3] != 0) {
				sprintf(send_buffer2, "CD\t%d\n", adjacency_matrix[2][3]);
				strcat(send_buffer3, send_buffer2);
			}


			broadcast_topology_A(send_buffer3, s1, s);
			usleep(100000);
			broadcast_topology_B(send_buffer3, s1, s);
			usleep(100000);
			broadcast_topology_C(send_buffer3, s1, s);
			usleep(100000);
			broadcast_topology_D(send_buffer3, s1, s);
			usleep(10000);

			prim_MST_algo(adjacency_matrix);
			break;

		}

	}

	return 0;
}

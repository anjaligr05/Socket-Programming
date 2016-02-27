
/****************************************EE 450 Socket Programming *******************************/
/**************************************Author: Anjali Gopal Reddy ********************************/


/*Server program*/
#include "server450.h"
#include "util.h"

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
		head->num_servers++;
	} else {
		right = head;
		while (right->next != NULL)
			right = right->next;
		right->next = temp;
		right = temp;
		head->num_servers++;
		right->next = NULL;
	}

	return head;
}
void *get_in_addr(struct sockaddr *server_addr)
{
	//Ipv4
	if (server_addr->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)server_addr)->sin_addr);
	}//IPv6
	else
	return &(((struct sockaddr_in6*)server_addr)->sin6_addr);
}

int main(int argc, char *argv[]) {

	// listen on sockect_fd, new connection on client_fd
	int socket_fd, client_fd;
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

	/*Port Number- Dynamically configured for TCP*/
	/*Retrieve the locallybound	name of the specified socket and store it in the sockaddr structure*/
	/*if (getsockname(socket_fd, (struct sockaddr *) &server_addr,
			(socklen_t *) &addrlen) == -1) {
		perror("getsockname");
		exit(1);
	}*/


	/*Set IP address to localhost*/
/*	if ((he = gethostbyname("localhost")) == NULL) {
		perror("gethostbyname");
		exit(1);
	}*/

//	memcpy(&server_addr.sin_addr, he->h_addr_list[0], he->h_length);

	/*Set bits to zero*/
//	memset(server_addr.sin_zero, '\0', sizeof server_addr.sin_zero);

	// printf("Local IP address is: %s\n", inet_ntoa(server_addr.sin_addr));
	//printf("Local port is: %d\n", (int) ntohs(res));


	/*listen operation*/
	if(listen(socket_fd,10)<0)
	{
		perror("listen");
		exit(1);
	}

	/*Initialise Data Structue to hold the neighbour information*/
		server_info_node *server_info_ptr = (server_info_node*) malloc(
				sizeof(server_info_node));
		server_list_obj *head = NULL;

		if (socket_fd < 0) {
			printf("Error opening socket!\n");
			return -1;
		}
		/*Server reads input file*/
		FILE *file_ptr;
		char buf[1026];

		file_ptr = fopen("serverA.txt", "r");
		if (file_ptr == NULL) {
			fprintf(stderr, "Cannot open file for reading!\n");
			perror("Error");
		}

		while (fgets(buf, sizeof(buf), file_ptr) != NULL) {

			sscanf(buf, "%s\t%d", server_info_ptr->server_name,
					&server_info_ptr->cost);
			head = append_server(server_info_ptr, head);
		}
		server_list_obj *start;
			start = head;

	/*Accept operation*/
//	while(1) {  // main accept() loop
	        sin_size = sizeof their_addr;
	        client_fd = accept(socket_fd, (struct sockaddr *)&their_addr, &sin_size);
	        if (client_fd == -1) {
	            perror("accept");
	            //continue;
	            exit(1);
	        }

	       inet_ntop(their_addr.ss_family,get_in_addr((struct sockaddr *)&their_addr),
	            s, sizeof s);
	        printf("server: got connection from %s\n", s);

	        printf("Info=%s\n",start->obj->server_name);
	        while (start != NULL) {
	        		send(client_fd,start->obj->server_name,strlen(start->obj->server_name),0);
	        		start = start->next;
	        	}
//	}
//	 close(client_fd);
//	server_fd=accept(socket_fd,(struct sockaddr *)&server_addr,(socklen_t *)&addrlen);






	return 0;
}

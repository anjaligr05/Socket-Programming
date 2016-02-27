#define BACKLOG 10
#define MAXLENGTH 100
#define CLIENTPORT "25949"
#define URL "nunki.usc.edu"
#define TOTALSERVERS 4
#define SERVER_A_PORT "21949"
#define SERVER_B_PORT "22949"
#define SERVER_C_PORT "23949"
#define SERVER_D_PORT "24949"

static int *flagA;
static int* flagB;
static int* flagC;
static int* flagD;
static int (*adjacency_matrix)[4];
static int exit_status;



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/mman.h>
#include <limits.h>
#include <stdbool.h>
#include <sys/socket.h>

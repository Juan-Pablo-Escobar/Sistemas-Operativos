#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>

#define PORT 6666
#define BUF_SIZE 128

struct client_t {
	int socket;
	int rxState;
	char name[20];
};

int client_sd[10];
int trash_client_sd[1];
pthread_t rxThreadId[10];
pthread_t trash_thread[1];
pthread_t consoleThreadId;
int threads = 0;
struct client_t client[10];
struct client_t trash_client[1];



int findClient(int socket){
	for(int i=0;i<threads;i++){
		if(client[i].socket==socket){
			return i;
		}
	}
	return -1;
}

void delClient(int index){
	client[index].rxState = 0;
	int status;
	status = write(client[index].socket,":exit", strlen(":exit") + 1);
	if (-1 == status) {
		perror("Server write to client fails: ");
	}
	close(client[index].socket);
	for(int i=index;i<threads-1;i++){
		client_sd[i] = client_sd[i+1];
		rxThreadId[i] = rxThreadId[i+1];
		client[i] = client[i+1];
	}
	threads --;
}


void* readThread(void *arg) {
	struct client_t *client_temp1 = ((struct client_t*) arg);
	struct client_t client_temp;
	client_temp  = client_temp1[0];
	ssize_t numOfBytes;
	char buf[BUF_SIZE];
	int logged = 0;
	char name[20];

	while (1) {
		numOfBytes = read(client_temp.socket, buf, BUF_SIZE);
		if(findClient(client_temp.socket)==-1){
			return NULL;
		}
		if (0 == numOfBytes) {
			printf("client closed the socket end\n");
			break;
		} else if (-1 == numOfBytes) {
			perror("ReadThread read() fails: ");
			break;
		} else {
			char buf_temp[30];
			strcpy(buf_temp,buf);
			char * token = strtok(buf_temp, " ");
			if(!strcmp(token,":exit")){
				break;
			}else if(!strcmp(token,":name")){
				token = strtok(NULL, " ");
				if( token != NULL ){
					strcpy(client_temp.name,token);
					strcpy(client[findClient(client_temp.socket)].name,token);
					logged = 1;
					int status;
					char var_temp[30];
					sprintf(var_temp,"logged as %s\0",client_temp.name);
					status = write(client_temp.socket,var_temp, strlen(var_temp) + 1);
					if (-1 == status) {
						perror("Server write to client fails: ");
						break;
					}
					printf("User [%d] has being logged as %s\n",client_temp.socket,client_temp.name);
					for (int i = 0; i < threads; i++) {
						if (client[i].socket != client_temp.socket) {
							char var_temp[30];
							sprintf(var_temp,"%s has entered the chat",client_temp.name);
							status = write(client[i].socket,var_temp, strlen(var_temp) + 1);
							if (-1 == status) {
								perror("Server write to client fails: ");
								break;
							}
						}
					}
				}
			}else{
				if(logged){
					printf("from client [%d]: %s\n", client_temp.socket, buf);
					int status;
					for (int i = 0; i < threads; i++) {
						if (client[i].socket != client_temp.socket) {
							char var_temp[30];
							sprintf(var_temp,"%s: %s",client_temp.name,buf);
							status = write(client[i].socket,var_temp, strlen(var_temp) + 1);
							if (-1 == status) {
								perror("Server write to client fails: ");
								break;
							}
						}
					}
				}else{
					int status;
					char var_temp[30];
					sprintf(var_temp,"Please login to send or see mesagges\0");
					status = write(client_temp.socket,var_temp, strlen(var_temp) + 1);
					if (-1 == status) {
						perror("Server write to client fails: ");
						break;
					}
					printf("User [%d] has tried to text without login\n",client_temp.socket,client_temp.name);
				}

			}

		}
	}
	printf("Terminate Pthread for reading asdas\n");
	client_temp.rxState = 0;
	delClient(findClient(client_temp.socket));
	return NULL;
}


int IsDigit(char a[]){
	int i = 0;
	while(1){
		if(a[i]==NULL){
			break;
		}
		if(!isdigit(a[i])){
			return 0;
		}
		i++;
	}
	return 1;
}


void* commandThread(){
	while(1){
		char buf[BUF_SIZE];
		if ( fgets(buf,BUF_SIZE,stdin) == NULL){
			printf("Fgets NULL\n");
		}
		char * token = strtok(buf, " ");
		if(!strcmp(token,"lsusrs\n")){
			for(int i =0;i<threads;i++){
				printf("Socket: %d --- User Name: %s\n",client[i].socket,client[i].name);
			}
		}else if(!strcmp(token,"disconnect")){
			token = strtok(NULL, " ");
			if(token != NULL){
				if(!IsDigit(token)){
					int tokenT = atoi(token);
					delClient(findClient(tokenT));
				}
			}
		}
	}
	return NULL;
}

int main(int argc, char *argv[]) {

	char buf[BUF_SIZE];
	int status;
	int enable = 1;
	int server_sd;

	// 1. Ignore SIGPIPE
	signal(SIGPIPE, SIG_IGN);

	// 2. Create socket
	server_sd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_sd == -1) {
		perror("Socket creation fails\n");
		exit(EXIT_FAILURE);
	}
	printf("Socket created\n");

	// 3. turn off bind address checking
	status = setsockopt(server_sd, SOL_SOCKET, SO_REUSEADDR, (int*) &enable,
			sizeof(enable));
	if (-1 == status) {
		perror("setsockopt error: ");
	}

	//4. BIND the socket to an address
	// Prepare the address
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(PORT);

	status = bind(server_sd, (struct sockaddr*) &addr, sizeof(addr));
	if (-1 == status) {
		perror("Bind fails: ");
		close(server_sd);
		exit(EXIT_FAILURE);
	}
	printf("Socket binded\n");

	// 5. Set backlog

	status = listen(server_sd, 10);

	if (-1 == status) {
		perror("Listen fails: ");
		close(server_sd);
		exit(EXIT_FAILURE);
	}

	printf("Server listening\n");
	status = pthread_create(&consoleThreadId, NULL, &commandThread,(void*)client);
	if (-1 == status) {
		perror("Pthread read fails: ");
		close(server_sd);
		exit(EXIT_FAILURE);
	}

	while (1) {
		if (threads < 10) {
			// 6. Accept:
			printf("Waiting for a client\n");
			int temp = accept(server_sd, NULL, NULL);
			client_sd[threads] = temp;

			printf("Client connected\n");
			if (-1 == client_sd[threads]) {
				perror("Accept fails: ");
				close(server_sd);
				exit(EXIT_FAILURE);
			}
			// 7. Create a thread for receiving messages from client
			client[threads].socket = client_sd[threads];
			client[threads].rxState = 1;
			strcpy(client[threads].name,"");

			printf("Create Pthread for reading\n");
			status = pthread_create(&rxThreadId[threads], NULL, &readThread,
					&client[threads]);
			if (-1 == status) {
				perror("Pthread read fails: ");
				close(server_sd);
				exit(EXIT_FAILURE);
			}
			threads++;
		}

	}
	for (int i = 0; i > threads; i++) {
		pthread_join(rxThreadId[i], NULL);
	}
	pthread_join(consoleThreadId,NULL);

	exit(EXIT_SUCCESS);
}

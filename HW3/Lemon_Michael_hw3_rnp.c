// Michael Lemon
// 4/21/21
// Computer Science 350 Section 01
// Homework #3: Random Numbers Problem
// GCC in Linux


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <errno.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <netinet/in.h>


//message struct, holds pid and an int
struct message {
	int data;
	pid_t pid;
};

void create_processes(int num_of_clients);
void run_client();
void run_server();


//the designated ip and port combo
char server_ip[] = "127.0.0.1";
int server_port = 1867;


int main(int argc, char const *argv[])
{

	//select preferred # of clients
	int num_of_clients = 3;

	create_processes(num_of_clients);


	return 0;
}

void create_processes(int num_of_clients){

	//for each client specified by the method, fork
	for (int i = 0; i < num_of_clients; ++i)
	{
		pid_t pid = fork();


		//errorcheck for the fork
		if (pid < 0) {
			puts("Error in forking");
			exit(1);
		}

		if (pid == 0) {
			//We are in child, run client
		 	run_client();
		} else {
			//We are in parent, run server
			run_server();
		}
	}

}

void run_client(){

	sleep(1);

	pid_t pid = getpid();

	int socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);

	if (socket_descriptor == -1){
		puts("Client: Could not get socket.");
		exit(1);
	}

	//configure socket address
	struct sockaddr_in socket_address;
	memset(&socket_address, 0, sizeof(socket_address));
	socket_address.sin_family = AF_INET;
	socket_address.sin_port = htons(server_port);
	inet_aton(server_ip, &(socket_address.sin_addr));

	//attempt to connect and check for error
	if (connect(socket_descriptor, (struct sockaddr*) & socket_address, sizeof(socket_address)) == -1){
		printf("Client %d: Error connecting", pid);
		exit(1);
	}

	//seed srand
	time_t t;
	srand((unsigned) (time(&t)));

	//set num of messages
	int num_of_messages = 10;
	//for each message, send it to the server in a struct
	for (int i = 0; i < num_of_messages; ++i) {
		struct message message = { .data = rand(), pid = pid};
		if ((write(socket_descriptor, &message, sizeof(struct message))) == -1){
			printf("Client %d: Error %d writing #%d.\n", pid , errno, message.data);
			exit(1);
		} else {
			printf("Client %d: Wrote message %d/10 with value %d\n",pid, i+1, message.data);
		}
		sleep(1);
	}

	//finish writing and close
	printf("Client %d: Finished writing messages.\n",pid);

	close(socket_descriptor);

	return;

}

void run_server(){


	int socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_descriptor == -1){
		printf("Server: Error getting socket.\n");
		exit(1);
	}

	//set timeout struct
	struct timeval timeout;
	memset(&timeout, 0, sizeof(timeout));
	timeout.tv_sec = 10;

	//set options for the server's socket
	if (setsockopt(socket_descriptor, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) == -1) {
		printf("Server: Error setting sockopts.\n");
	}

	struct sockaddr_in socket_address;

	// configure the socket address
	memset(&socket_address, 0, sizeof(socket_address));
	socket_address.sin_family = AF_INET;
	socket_address.sin_port = htons(server_port);
	inet_aton(server_ip, &(socket_address.sin_addr));

	//attempt to bind and check for errors
	if (bind(socket_descriptor, (struct sockaddr*)&socket_address, sizeof(socket_address)) == -1){
		puts("Server: Error binding");
		exit(1);
	}

	//attempt to listen and check for errors
	if (listen(socket_descriptor, 5) == -1){
		puts("Server: Error initializing listen");
		exit(1);
	} else {
		puts("Server: Listening for connections.");
	}

	//10 times, allow connection attempts
	for (int i = 0; i < 10; i++){
		struct sockaddr connection_addr;
		socklen_t connection_addr_size = sizeof(connection_addr);
		char* client_ip = NULL;

		int connection_descriptor = accept(socket_descriptor, &connection_addr, &connection_addr_size);
		if (connection_descriptor == -1) {
			if ((errno != EINTR) && (errno != EAGAIN)){
				printf("Server %d: Error accepting connection:Error %d.\n",getpid(), errno);
			}
			continue;

		} else {
			client_ip = inet_ntoa(((struct sockaddr_in*) & connection_addr)->sin_addr);

			printf("Server %d: Accepted connection from IP %s...\n",getpid(), client_ip);
		}

		//make struct for the message
		ssize_t message_size = 0;
		struct message message;
		//attempt to grab message, print it
		while ((message_size = read(connection_descriptor, &message, sizeof(message))) > 0) {
			printf("Server %d: Client %d with IP %s sent #%d.\n",getpid(), message.pid, client_ip, message.data);
		}
		//when there is no more message, close connection
		if (message_size == 0) {
			printf("Server %d: Client %d closed connection.\n", getpid(), message.pid);
		} else {
			if (message_size == -1){
				//error check and timeout check
				if (errno = EAGAIN){
					printf("Server %d: Timed out waiting for %s.\n",getpid(), client_ip);
				} else {
					if (errno != EINTR) {
						printf("Server %d: Error recieving message: Error %d",getpid(), errno);
					}
				}
			}
		}	
	}


	//close socket and announce it
	close(socket_descriptor);

	puts("Server: Closed socket.\n");

	return;
}
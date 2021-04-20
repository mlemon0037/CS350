//Michael Lemon
//CS350 P23
//GCC in Linux

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

struct message {
	char* message;
};

void run_client();
void run_server();

char socket_path[] = "/tmp/socket";

int main(int argc, char const *argv[])
{
	pid_t pid = fork();

	if (pid < 0){
		puts("Could not fork");
		exit(1);
	}

	if (pid == 0){
		run_client();
	} else {
		run_server();
	}

	return 0;
}

void run_client(){

	sleep(1);

	int socket_descriptor = socket(AF_UNIX, SOCK_STREAM, 0);

	if (socket_descriptor == -1){
		puts("Client: Could not get socket");
		exit(1);
	}

	struct sockaddr_un socket_address;
	memset(&socket_address, 0, sizeof(socket_address));
	socket_address.sun_family = AF_UNIX;
	strcpy(socket_address.sun_path, socket_path);

	if (connect(socket_descriptor, (struct sockaddr*)&socket_address, sizeof(socket_address)) == -1){
		puts("Client: Problem connecting to socket");
		exit(1);
	}

	struct message message1 = { "[This is message #1]" };
	struct message message2 = { "[This is message #2]" };

	write(socket_descriptor, &message1, sizeof(message1));
	printf("Client: Wrote message %s.\n", message1.message);
	write(socket_descriptor, &message2, sizeof(message2));
	printf("Client: Wrote message %s.\n", message2.message);

	puts("Client: Finished");

	close(socket_descriptor);

	return;
}

void run_server(){

	int socket_descriptor = socket(AF_UNIX, SOCK_STREAM, 0);

	if (socket_descriptor == -1){
		puts("Server: Could not get socket");
		exit(1);
	}

	struct timeval timeout;
	memset(&timeout, 0, sizeof(timeout));
	timeout.tv_sec = 10;
	if (setsockopt(socket_descriptor, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) == -1) {
		printf("Server: Error setting socket option %d.\n", errno);
		exit(1);
	}

	struct sockaddr_un socket_address;
	memset(&socket_address, 0, sizeof(socket_address));
	socket_address.sun_family = AF_UNIX;
	strcpy(socket_address.sun_path, socket_path);

	unlink(socket_path);

	if (bind(socket_descriptor, (struct sockaddr*)&socket_address, sizeof(socket_address)) == -1) {
		puts("Server: Error binding socket");
	} else {
		puts("Server: Bound to socket");
	}

	if (listen(socket_descriptor, 3) == -1){
		puts("Error listenting for connections");
		exit(1);
	} else {
		puts("Server: Listening for connections");
	}

	for (int i = 0; i < 5; ++i)
	{
		int connection_descriptor = accept(socket_descriptor, NULL, NULL);

		if (connection_descriptor == -1){
			if ((errno != EINTR) && (errno != EAGAIN)) {
				printf("Server: Error accepting connection %d.\n", errno);
			}

			continue;
		} else {
			puts("Server: accepted connection.");
		}

		ssize_t message_size = 0;
		struct message message;

		while ((message_size = read(connection_descriptor, &message, sizeof(message))) > 0) {
			printf("Server: Recieved message: %s.\n", message.message);
		}

		if (message_size == 0){
			puts("Server: Client finished sending data.");
		} else {
			if (message_size == -1){
				if (errno == EAGAIN) {
					puts("Server: timed out waiting for client.");
				} else {
					if (errno == EINTR) {
						printf("Server: error waitng for message: %d.\n", errno);
					}
				}
			}
		}
	}

	close(socket_descriptor);
	puts("Server: closed socket.");

	return;
}
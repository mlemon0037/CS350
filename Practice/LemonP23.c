//Michael Lemon
//CS350 P23
//GCC in Linux
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

void sig_handler(int sig);

int signal_recieved = 0;

struct message {
	char* message;
};


int main(int argc, char const *argv[])
{

	struct message pipe_to_parent[2];

	int pipe_status = pipe(pipe_to_parent);

	if (pipe_status == -1){
		puts("unable to create pipe");
		exit(1);
	}

	pid_t pid = fork();
	if (pid < 0) {
		puts("unable to create pipe");
		exit(1);
	}

	if (pid == 0){

		struct message message1 = { "This is the first message" };
		write(pipe_to_parent[1].message, &message1, sizeof(message1));

		struct message message2 = { "This is the second message" };
		write(pipe_to_parent[1].message, &message2, sizeof(message2));


		close(&pipe_to_parent[1]);


	} else {
		close(pipe_to_parent[1]);

		struct message pipe_input;

		while (read(pipe_to_parent[0], &pipe_input, sizeof(pipe_input))){
			printf("Parent recieved: %s\n", pipe_input.message);
		}

		puts("parent has finished reading from pipe");
	}
	
	return 0;
}
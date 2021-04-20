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

typedef struct {
	char* message;
} message;


int main(int argc, char const *argv[])
{
	pid_t pid = fork();
	if (pid < 0){
		puts("Could not fork");
		exit(1);
	}

	if (pid == 0){
		
		signal(SIGUSR1, sig_handler);

		while (signal_recieved == 0){
			puts("Child is waiting for signal");
			sleep(1);
		}

	printf("Child has recieved signal %d from parent", signal_recieved);
	signal_recieved = 0;

	} else {

		sleep(3);

		puts("Sending signal to child.");
		kill(pid, SIGUSR1);
	}

	return 0;
}

void sig_handler(int sig){

}
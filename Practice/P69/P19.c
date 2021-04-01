//Michael Lemon
//CS350 P19
//GCC
#include <stdio.h>
#include <sys/types.h> 
#include <unistd.h>

int main(int argc, char const *argv[])
{
	int i = 1;
	pid_t pid = fork();


	if (pid == 0){
		i--;
		printf("In the child i = %d.\n", i);
	} else {
		i++;
		wait(NULL);
		printf("In the parent i = %d.\n", i);
	}
	return 0;
}
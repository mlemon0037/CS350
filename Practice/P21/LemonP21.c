#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/types.h>

void* decrement(void* param);

//file scoped int i
int i = 1;

int main(int argc, char const *argv[])
{
	pthread_t tid;

	if (pthread_create(&tid, NULL, decrement, (void*)NULL) != 0) {
		puts("Could not create thread");
		exit(1);
	}

	pthread_join(tid, NULL);

	i++;

	printf("[Parent Thread] Value of i is %d.\n", i);

	return 0;
}

void* decrement(void*  param)
{
	i--;

	pthread_t self_tid = pthread_self();

	printf("[Child Thread %lu] Value of i is %d.\n", self_tid, i);

	return (void*) 0;
}
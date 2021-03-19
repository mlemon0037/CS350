#include <stdio.h>
#include <stdlib.h>

/*
Michael Lemon
CS 350 Participation 15
GCC
*/

void enqueue(int arr[], int* length, int val);
int dequeue(int arr[], int* length);
void print(int arr[], int length);

int main(int argc, char *argv[])
{
	int length = 0;
	int queue[5] = {};
	enqueue(queue, &length, 13);
	enqueue(queue, &length, 1);
	enqueue(queue, &length, 5);
	enqueue(queue, &length, 11);
	enqueue(queue, &length, 53);
	enqueue(queue, &length, 22);

	printf("\nPrinting Queue Below: \n");
	print(queue, length);


	printf("\nDisplaying Dequeued values below: \n");
	printf("%d\n", dequeue(queue, &length));
	printf("%d\n", dequeue(queue, &length));
	printf("%d\n", dequeue(queue, &length));
	printf("%d\n", dequeue(queue, &length));
	printf("%d\n", dequeue(queue, &length));
}

void enqueue(int arr[], int* length, int val) {
	if (*length == 5){
		printf("Queue max size reached, item not enqueued\n");
	} else {
		arr[*length] = val;
		(*length)++;
	}
	
}

int dequeue(int arr[], int* length) {
	if (*length == 0){
		printf("Queue is empty, item not dequeued\n");
	} else {
		int val = arr[0];
		for (int i = 0; i < *length - 1; i++){
			arr[i] = arr[i + 1];
		}
		(*length)--;
		return val;
	}
	return 0;
}

void print(int arr[], int length) {
	for (int i = 0; i < length; i++){
		printf("%d\n", arr[i]);
	}
}
#include <stdio.h>

/*
Michael Lemon
CS 350 Participation 13
GCC
*/

int main()
{
	int arr[] = {1, 16, 13, 1, 3, 5};
	size_t size = sizeof(arr)/sizeof(arr[0]);

	FILE * fileptr;
	fileptr = fopen("output.txt", "w");

	for (int i = 0; i < size; i++){
		fprintf(fileptr, "%d\n", arr[i]);
	}

	return 0;
}
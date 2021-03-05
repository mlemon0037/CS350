// Michael Lemon
// 3/4/2021
// Computer Science 350 Section 001
// Practice 12
// GCC
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {

	char* str = "secret text youre not allowed to see.";

	printf("%s\n", str);

	time_t t;
	srand((unsigned) time(&t));

	size_t size = 37;
	char key[size];
	printf("%li\n", size);
	for (int i = 0; i < size; i++)
	{
		char rand_char = rand() % (125 + 1 - 33) + 33;
		key[i] = rand_char;
	}

	printf("%s\n", key);

	char cipher[size];
	for (int i = 0; i < size; i++)
	{
		cipher[i] = str[i] ^ key[i];
	}
	printf("%s\n", cipher);

	char plaintext[size];
	for (int i = 0; i < size; i++)
	{
		plaintext[i] = cipher[i] ^ key[i];
	}
	printf("%s\n", plaintext);
}
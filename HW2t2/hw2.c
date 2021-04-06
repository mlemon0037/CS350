// Firstname Lastname
// 4/4/21
// Computer Science 350 Section 001
// Homework #2: West Virginia Population Problem
// Linux GCC

#include <stdio.h>
#include <stdlib.h>


typedef struct {
	char name[17];
	char FIPS[12];
	char seat[22];
	int year;
	int pop;
	int area;
	double pop_dens;
} county;

typedef struct {
	county data;
	struct node* next;
} node;

int add(node** head, county item);
county nextCounty(FILE* counties);

int main(int argc, char const *argv[])
{
	FILE* counties = fopen("counties.txt", "r");

	node head = NULL;

	if (counties == NULL) {
		puts("File not found");
		exit(1);
	}

	char buf[50];
	for (int i = 0; i < 7; i++) {
		fscanf(counties, "%s", buf);
	}
	while (!feof(counties)) {
		struct county next = nextCounty(counties);
		add(&list, next);
	}

	fclose(counties);
	return 0;
	return 0;
}

int add(node** head, county item) {
	if (head == NULL){
		node new = { .data = item, .next = NULL};
		head = &new;
	} else {

	}
}
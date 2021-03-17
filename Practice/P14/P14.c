#include <stdio.h>
#include <stdlib.h>


/*
Michael Lemon
CS 350 Participation 14
GCC
*/



struct node {
	struct node *next;
	int data;
};


void add(int val);
void print();

struct node *head = NULL;

int main(int argc, char *argv[])
{
	add(5);
	add(1);
	add(5);
	add(3);
	add(12);
	add(531);
	print(&head);
	return 0;
}

void add(int val) {
	struct node* newPtr = malloc(sizeof(struct node));
	newPtr->next = NULL;
	newPtr->data = val;

	if (head != NULL){
	struct node* ptr = head;
	while (ptr->next != NULL){
		ptr = ptr->next;
	}
	ptr->next = newPtr;
	} else {
		head = newPtr;
	}
}
void print() {
	struct node* ptr = head;

	while (ptr != NULL){
		printf("%d\n", ptr->data);
		ptr = ptr->next;
	}
	return;
}
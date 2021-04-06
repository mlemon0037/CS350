// Lemon Michael
// 4/4/21
// Computer Science 350 Section 001
// Homework #2: West Virginia Population Problem
// Linux GCC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct county {
	char name[17];
	char FIPS[12];
	char seat[22];
	int year;
	int pop;
	int area;
	double pop_dens;
} county;

typedef struct node {
	county data;
	struct node* next;
} node;

void add(node** head, struct county item);
void print(node** head);
void delete(node** head, char* str);
void write(node** head);
struct county nextCounty(FILE* counties);

int main(int argc, char const* argv[])
{
	//create head
	node* head = NULL;
	//create file from counties.txt
	FILE* counties = fopen("counties.txt", "r");

	//check if file exists
	if (counties == NULL) {
		puts("File not found");
		exit(1);
	}

	//for each county, find next county and insert it
	for (int i = 0; i < 56; ++i) {
		struct county next = nextCounty(counties);
		add(&head, next);
	}

	//test code
	// print(&head);
	// printf("\nDeleting Ohio and Brooke\n\n");
	delete(&head, "Ohio");
	delete(&head, "Brooke");
	// print(&head);

	//close the file and write the data
	fclose(counties);
	write(&head);
	return 0;
}

//takes a list and county as parameters
//puts the county in the list in descending sorted order based on its pop_dens
void add(node** head, struct county item) {

	//create our new node
	node* new = (node*)malloc(sizeof(node));
	new->data = item;
	new->next = NULL;

	//check if head is null, if it is just set it to the new node
	if (*head != NULL) {

		//create current and previous nodes
		node* cur = *head;
		node* prev = cur;

		//while current isnt null, check if the new node's density is higher than current's
		while (cur->next != NULL) {
			//if new node's density is higher than current's, insert current at that position
			if (item.pop_dens > cur->data.pop_dens){
				//insert new node
				new->next = cur;
				prev->next = new;
				return;
			}
			
			//advance previous and current nodes
			prev = cur;
			cur = cur->next;
		}

		//if we dont return out before now, insert new node at end of list
		cur->next = new;
	}
	else {
		//head is null, set it to new node
		*head = new;
	}
	return;
}

//deletes a given county name from a list
void delete(node** head, char* str){

	//define our current and previous nodes
	node* cur = *head;
	node* prev = *head;

	//while cur isnt null, compare our string against the node string
	while(cur != NULL){
		//compare the names of the given char* and the node's name
		if (strcmp(cur->data.name, str) == 0){
			//if they match, reference around the current node
			prev->next = cur->next;
			break;
		}
		//advance current and previous nodes
		prev = cur;
		cur = cur->next;
	}
	return;
}

//prints context of the list to the console
void print(node** head){
	//current node
	node* cur = *head;

	//until cur is null, print the data associated with each node
	do {
		cur = cur->next;
		printf("Name: %-17s FIPS: %-12s Seat: %-22s Year: %-d Pop: %-d Area: %-d Pop_Dens: %-.2f\n", cur->data.name, cur->data.FIPS, cur->data.seat, cur->data.year, cur->data.pop, cur->data.area, cur->data.pop_dens);
	} while (cur->next != NULL);

	return;
}

//writes county data from given head node
//outputs a line of labels followed by the data
void write(node** head){
	FILE *file = fopen("output.csv", "w");

	//prints labels with formatting at top of file
	fprintf(file, "%s,%s,%s,%s,%s,%s,%s\n", "County","FIPS Code","County Seat","Established","Population","Area","Pop Density");
	//define our cur node for iterating over list
	node* cur = *head;
	cur = cur->next;

	//while cur is not null, print the data for the county
	while (cur != NULL) {
		fprintf(file, "%s,%s,%s,%d,%d,%d,%.2f\n", cur->data.name, cur->data.FIPS, cur->data.seat, cur->data.year, cur->data.pop, cur->data.area, cur->data.pop_dens);
		cur = cur->next;
	}
	fclose(file);
}

//trims whitespace
void trim (char* str){
	//define index and i
	int index, i;

    index = -1;
    i = 0;

    //go to the end, setting index to last known non whitespace character
    while(str[i] != '\0') {
    	//if we ever get whitespace, store that index
        if(str[i] != ' ') {
            index= i;
        }
        i++;
    }
    //set index+1, the first extra whitespace, to the null char
    str[index + 1] = '\0';
}

//method to grab next county from the given file
//returns the county from file
struct county nextCounty(FILE* counties) {
	struct county county;

	fgets(county.name, 17, counties);
	trim(county.name);
	fgets(county.FIPS, 12, counties);
	trim(county.FIPS);
	fgets(county.seat, 22, counties);
	trim(county.seat);
	char temp[14];
	fgets(temp, 14, counties);
	county.year = atoi(temp);
	char temp2[13];
	fgets(temp2, 13, counties);
	county.pop = atoi(temp2);
	char temp3[5];
	fgets(temp3, 5, counties);
	county.area = atoi(temp3);
	county.pop_dens = ((float)county.pop)/((float)county.area);

	fgetc(counties);

	return county;
}
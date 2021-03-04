// Michael Lemon
// 2/26/2021
// Computer Science 350 Section 001
// Homework #1: WVU Enrollment Problem
// GCC with '-lm'
#include <stdio.h>
#include <math.h>

double reqGrowthRate(int *initial, int *target);

int main(){

	//change desired initial enrollment here
	int initialEnrollment = 29333;
	int userTarget;

	puts("Please give target enrollment on the next line:");
	//require valid user input, loop until we get it
	while(1){
		//break if input is valid
		if (scanf("%d", &userTarget) && userTarget > 0){
			break;
		}
		puts("Invalid input, try again:");
		//clear input buffer
		while ( getchar() != '\n' );
	}

	double rate = reqGrowthRate(&initialEnrollment, &userTarget);

	//pretty print required growth 
	printf("Required Growth Rate: %.1f%%\n", rate * 100);
	printf("This Growth is: ");

	//check for reasonability and print
	if (rate >= 0.04) {
		printf("Unreasonable");
	} else if (rate >= 0.02) {
		printf("Very Ambitious");
	} else if (rate >= 0.01) {
		printf("Ambitous");
	} else if (rate >= 0) {
		printf("Reasonable");
	} else {
		printf("Negative");
	}
	printf("\n\n");

	for (int i = 2019; i <= 2069; i++) {
		int currEnrollment = initialEnrollment * pow(1 + rate, i - 2019);
		printf("%i Enrollment: %i\n", i, currEnrollment);
	}
}

//pass pointers and execute the formula for multi year growth
double reqGrowthRate(int *initial, int *target){
	return pow((double) *target / (double) *initial, (1.0F/11.0F)) - 1;
}
// Michael Lemon
// 2/26/2021
// Computer Science 350 Section 001
// Homework #1: WVU Enrollment Problem
// GCC
#include <stdio.h>
#include <math.h>

double reqGrowthRate(int *initial, int *target);

int main(){
	int initialEnrollment = 29333;
	int userTarget;

	puts("Please give target enrollment on the next line:");
	while(1){
		if (scanf("%d", &userTarget) && userTarget > 0){
			break;
		}
		puts("Invalid input, try again:");
		while ( getchar() != '\n' );
	}

	double rate = reqGrowthRate(&initialEnrollment, &userTarget);

	printf("%.1f%%\n", rate);
	printf("%.1f%%\n", rate / 100.0F);
}

double reqGrowthRate(int *initial, int *target){
	return pow((double) *target / (double) *initial, (1.0F/11.0F)) - 1;
}
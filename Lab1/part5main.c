#include <stdio.h>

/*
main.c
Aaron Knestaut
2/26/19

Takes in a user input number, then asks for 
user input numbers that many times.
The program spits out the sum of all the nums
and the average.
*/

void main(){
	int loop;
	int sum;
	double avg;
	
	printf("\nPlease enter the number of entries: ");
	scanf("%d",&loop);

	for(int i = 1; i <= loop; i++){
		int temp = getOneNumber(i);
		sum = sum + temp;
	}

	avg = sum / loop;
	
	printf("\nThe sum of these numbers is %d. Their average is %.2f.\n", sum, avg);
}

int getOneNumber(int x){
	int output;
	printf("\nEnter integer #%d:", x);
	scanf("%d", &output);

	return output;
}

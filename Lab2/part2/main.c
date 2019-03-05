/*
main.c

Aaron Knestaut
Cisc 210
3/5/19

Takes in a number and passes it into isEven
*/

#include <stdio.h>
#include <stdbool.h>
#include "numtype.h"

void main(){
	int num;

	printf("Enter a positive number: ");
	scanf("%d", &num);
/*
	if(isEven(num)){
		printf("The number %d is even\n", num);
	}
	else if(isOdd(num)){
		printf("The number %d is odd\n", num);
	}
	else{
		printf("Something went wrong. Oops\n");
	}
*/
	if(isPrime(num))
		printf("The number %d is prime\n", num);
	else if(!isPrime(num))
		printf("The number %d is not prime\n", num);
	else
		printf("Something went wrong. Oops.\n");
}

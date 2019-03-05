/*
numtype.c

Aaron Knestaut
Cisc 210
3/5/19

Takes in a number from main.c and determines if it
is even or odd, or prime
*/

#include <stdbool.h>

bool isEven(int num){
	int remainder;
	remainder =  num % 2;

	if(remainder == 0){
		return true;
	}
	else
		return false;
}

bool isOdd(int num){
	int remainder;
	remainder % 2;

	if(remainder != 0){
		return true;
	}
	else
		return false;
}

bool isPrime(int num){
	if(isEven(num)){
		return false;
	}
	
	for(int i = 2; i < num; i++){
		if((num % i) == 0)
			return false;
	}
	return true;
}

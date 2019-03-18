/*
main.c

Aaron Knestaut
Cisc 210
3/19/19

the main function for game.c that takes in user input
and outputs results
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "game.h"

void main(){
    char input[12];
    bool loop = true;
    printf("Welcome to rock / paper / scissors. Type 'exit' to quit.\n");

    while(loop){
        printf("Enter an option: ");
        scanf("%s", &input);
        if(input[0] == 'q'){
            printf("Exiting...\n");
            loop = false;
        }
        else if(strcmp(input, "rock") == 0 || strcmp(input, "paper") == 0 || strcmp(input, "scissors") == 0){
            if(run(input) == 0){
                printf("You win!\n");
            }
            else if(run(input) == 1){
                printf("You lose.\n");
            }
            else{
                printf("It's a tie.\n");
            }
        }
        else{
            printf("Invalid input. Try again.\n");
        }
    }
}


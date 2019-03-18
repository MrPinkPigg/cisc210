/*
game.c

Aaron Knestaut
Cisc 210
3/19/19

includes the function to process user input from main.c
*/

#include <string.h>
#include "game.h"

int run(char input[]){
    if(RANDNUM == ROCK){
        if(strcmp(input, "paper") == 0){
            return 0;
        }
        else if(strcmp(input, "scissors") == 0){
            return 1;
        }
        else{
            return 2;
        }
    }
    else if(RANDNUM == PAPER){
        if(strcmp(input, "scissors") == 0){
            return 0;
        }
        else if(strcmp(input, "rock") == 0){
            return 1;
        }
        else{
            return 2;
        }
    }
    else if(RANDNUM == SCISSORS){
        if(strcmp(input, "rock") == 0){
            return 0;
        }
        else if(strcmp(input, "paper") == 0){
            return 1;
        }
        else{
            return 2;
        }
    }
}


/*
main.c
Aaron Knestaut
Maria van Venrooy
Cisc 210
Final Pi Project - Bop It
main function
Runs a basic "BopIt" game, where you need to perform an action
quickly based on what the screen shows.
How to play:
	If the screen turns:
	PURPLE - BOP IT, just hit the joystick button
	YELLOW - TWIST IT, just twist the whole device horizontally,
			keep the sreen on top
	BLUE - FLIP IT, flip the device so the screen is upside down,
			then back
	GREEN - you got a point! the screen should change to a new color
			quickly
	RED - you got something wrong, and the game is over!
At the end of the game, the number you got right should display on the screen
Ctrl-C at any time should stop the game
*/

#define _GNU_SOURCE
#include <signal.h>
#include <sense/sense.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <linux/input.h>

float run = 1;
float click = 0;

/*
handles interupting the function with a ctrl-c
*/
void interruptHandler(){
    run = 0;
}

//determines if the joystick is pressed
void callbackFn(unsigned int code){
	switch(code){
		case KEY_ENTER:
			click = 1;
			break;
		default:
			click = 0;
	}
}

/*
main function, runs the game loop, handles the timer, and keeps track of the score
*/
void main(){
	//sets up all devices
	pi_framebuffer_t* framebuffer = getFBDevice();
	pi_i2c_t* device = geti2cDevice();
	pi_joystick_t* joystick = getJoystickDevice();
	coordinate_t data;

	if (device){
		configureAccelGyro(device);
		int score = 0;
		int returnVal = 0;

		signal(SIGINT,interruptHandler);

		/*
		show color instruction
		check for task completion
		if task is failed, run = 0
		if task completed, score++	
		*/

		while(run){
			//sets initial framebuffer to empty
			clearBitmap(framebuffer->bitmap,getColor(0, 0, 0));
			
			//determines a random event
			int val = 1;//rand()%3;

			//starts the some second timer
			time_t start = clock();

			//reset button to 'unclicked' 
			click = 0;
			
			//reset returnVal to 'action not completed'
			returnVal = 0;
			
			char eventCheckRun = 1;
			
			//while some seconds isnt hit, check for event input
			while((clock() - start) < 4000 - score && eventCheckRun){

				if (returnVal) {
					eventCheckRun = 0;	
				}
				else if(val == 0){ //BOP
					allPurple(framebuffer);
					returnVal = reader(val, joystick, device, data);
				}
				else if(val == 1){ //TWIST
					allYellow(framebuffer);
					returnVal = reader(val, joystick, device, data);
				}
				else{ //FLIP
					allBlue(framebuffer); 
					returnVal = reader(val, joystick, device, data);
				}
			}

			time_t timer2 = clock();

			if(returnVal == 1){ //Correct input was given, show green
				while((clock() - timer2) < 400000){
					allGreen(framebuffer);
				}
				score++;
			}
			else{
				while((clock() - timer2) < 400000){
					allRed(framebuffer);
				}
				
				run = 0; //user lost, stop running loop
			}
				
			
		}
		
		showScore(score, framebuffer);
	}
	freeFrameBuffer(framebuffer);
	freei2cDevice(device);
	freeJoystick(joystick);
	return 0;
}

/*
displays the score in binary at the end of the game
parameters:
	int score - takes the score from main and represents it on the screen
*/
void showScore (int score, pi_framebuffer_t* framebuffer)
{
		clearBitmap(framebuffer->bitmap,getColor(0,0,0));
		
		int row = 2;
		int comp = 128;

		//Display score in binary because real numbers are too hard
		for(int i = 0; i < 8; i++){
			framebuffer->bitmap->pixel[row][i] = getColor(0, 0, (score/comp) * 255);
			score = score - (score / comp * comp);
			comp = comp / 2;
		}
	
}


/*
reads the pi for a specific input based on which event is happening,
parameters:
	int check - the specific input to check for
returns:
	0 if the read event is incorrect
	1 if the read event is correct
*/
int reader(int val, pi_joystick_t *joystick, pi_i2c_t *device, coordinate_t *data){
	pollJoystick(&joystick,callbackFn,0);
	getGyroPosition(device, &data);

	//printf("%f %f %f\n", &data->x, &data->y, &data->z);
	//printf("%d\n", val);

	if(val == 0){ //BOP
		if(click){
			return 1;
		}
		else{
			return 0;
		}
	}

	 if(val == 1){ //TWIST	
		if(&data->z > 180){
			return 1;
		}
		else{
			return 0;
		}
	}
	
	else{ //FLIP
		if(&data->x > 100 && &data->y > 100){
			return 1;
		}
		else{
			return 0;
		}
	}

}


/*
turns the whole screen red
parameters:
	pi_framebuffer_t* framebuffer - takes in teh pi framebuffer to alter what the screen shows
*/
void allRed (pi_framebuffer_t* framebuffer) {
	for (int i = 0; i < 8; i ++)
	{
		for (int j = 0; j < 8; j++)
		{
			framebuffer->bitmap->pixel[i][j]= getColor(255,0,0);
		}
	}
}

/*
turns the whole screen green
parameters:
	pi_framebuffer_t* framebuffer - takes in teh pi framebuffer to alter what the screen shows
*/
void allGreen (pi_framebuffer_t* framebuffer) {
    for (int i = 0; i < 8; i ++)
    {
            for (int j = 0; j < 8; j++)
            {
                    framebuffer->bitmap->pixel[i][j]= getColor(0,255,0);
            }
    }
}

/*
turns the whole screen blue
parameters:
	pi_framebuffer_t* framebuffer - takes in teh pi framebuffer to alter what the screen shows
*/
void allBlue (pi_framebuffer_t* framebuffer) {
    for (int i = 0; i < 8; i ++)
    {
            for (int j = 0; j < 8; j++)
            {
                    framebuffer->bitmap->pixel[i][j]= getColor(0,0,255);
            }
    }
}

/*
turns the whole screen yellow
parameters:
	pi_framebuffer_t* framebuffer - takes in teh pi framebuffer to alter what the screen shows
*/
void allYellow (pi_framebuffer_t* framebuffer) {
    for (int i = 0; i < 8; i ++)
    {
            for (int j = 0; j < 8; j++)
            {
                    framebuffer->bitmap->pixel[i][j]= getColor(255,255,0);
            }
    }
}

/*
turns the whole screen purple
parameters:
	pi_framebuffer_t* framebuffer - takes in teh pi framebuffer to alter what the screen shows
*/
void allPurple (pi_framebuffer_t* framebuffer) {
    for (int i = 0; i < 8; i ++)
    {
            for (int j = 0; j < 8; j++)
            {
                    framebuffer->bitmap->pixel[i][j]= getColor(238,130,238);
            }
    }
}
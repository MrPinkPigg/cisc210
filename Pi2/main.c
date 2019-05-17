/**
Aaron Knestaut
Maria van Venrooy
Cisc 210

main.c

Etch-a-sketch

if you want to see the remains of what the project should of been
and why this is late, take a look at oldMain.c
oToo many segmentation faults to wrap our heads around, I guess
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

char run = 1;
uint16_t color;
int colorNum = 0;
float x = 0;
float y = 0;
pi_framebuffer_t* framebuffer;
float threshold = 1;

/*
handles interupting the function with a ctrl-c
*/
void interruptHandler(){
    run = 0;
}

/*
handles moving the light on the screen, and changing colors
based on the joystick
*/
void callbackFn(unsigned int code){
	switch(code){
		case KEY_UP:
			y=y==0?7:y-1;
			break;
		case KEY_DOWN:
			y=y==7?0:y+1;
			break;
		case KEY_RIGHT:
			x=x==7?0:x+1;
			break;
		case KEY_LEFT:
			x=x==0?7:x-1;
			break;
		case KEY_ENTER:
			if(colorNum == 0){
				color = getColor(0, 0, 255);
				colorNum = 1;
			}
			else if(colorNum == 1){
				color = getColor(0, 255, 0);
				colorNum = 2;
			}
			else if(colorNum == 2){
				color = getColor(255, 0, 0);
				colorNum = 0;
			}
			break;
		default:
			run=0;
	}
	setPixel(framebuffer->bitmap,x,y,color);
}

/*
main function of the game, initallizes everything and 
runs the main loop
*/
void main(){
	signal(SIGINT, interruptHandler);

	//sets up all devices
	framebuffer = getFBDevice();
	pi_joystick_t* joystick = getJoystickDevice();
	pi_i2c_t* device = geti2cDevice();
	configureAccelGyro(device);
	coordinate_t data;

	color = getColor(255, 0, 0);
	colorNum = 0;
	setPixel(framebuffer->bitmap,0,0,color);

	while(run){
		getAccelData(device, &data);
		int x = fabs(data.x);
		int y = fabs(data.y);
		int z = fabs(data.z);

		if(x > threshold || y > threshold || z > threshold){
			clearBitmap(framebuffer->bitmap,0);
		}

		pollJoystick(joystick, callbackFn, 1000);
	}

	clearBitmap(framebuffer->bitmap,0);
	freeFrameBuffer(framebuffer);
	freeJoystick(joystick);
	freei2cDevice(device);
}
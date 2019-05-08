/*
main.c

Aaron Knestaut
Maria van Venrooy
Cisc 210

the main file for the binary clock
*/

#include "framebuffer.h"
#include <time.h>
#include <stdio.h>
#include <unistd.h>

void main(){
	time_t rawtime;
	struct tm * timeinfo;

	pi_framebuffer_t* framebuffer = getFBDevice();

	while(1){
		clearBitmap(framebuffer->bitmap,getColor(0, 0, 0));

		time(&rawtime);
		timeinfo = localtime(&rawtime);

		int hours = timeinfo->tm_hour;
		int mins = timeinfo->tm_min;
		int secs = timeinfo->tm_sec;


		int row = 2;
		int comp = 128;

		//Hours
		for(int i = 0; i < 8; i++){
			framebuffer->bitmap->pixel[row][i] = getColor(0, 0, (hours/comp) * 255);
			hours = hours - (hours / comp * comp);
			comp = comp / 2;
		}

		row = 4;
		comp = 128;

		//Minutes
		for(int i = 0; i < 8; i++){
                        framebuffer->bitmap->pixel[row][i] = getColor(0, (mins/comp) * 255, 0);
                        mins = mins - (mins / comp * comp);
                        comp = comp / 2;
                }

		row = 6;
		comp = 128;

		//Seconds
		for(int i = 0; i < 8; i++){
                        framebuffer->bitmap->pixel[row][i] = getColor((secs/comp) * 255, 0, 0);
                        secs = secs - (secs / comp * comp);
                        comp = comp / 2;
                }
		sleep(1);
	}
	freeFrameBuffer(framebuffer);
	return 0;
}

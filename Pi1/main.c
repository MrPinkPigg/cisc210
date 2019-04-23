/*
main.c

Aaron Knestaut
Maria van Venrooy
Cisc 210

the main file for the binary clock
*/

#include "framebuffer.h"
#include "framebuffer.o"
#include <time.h>
#include <stdio.>

void main(){
	static int seconds_last = 99;
	char TimeString[128];

	timeval curTime;
	gettimeofday(&curTime, NULL);
	if (seconds_last == curTime.tv_sec)
		return;

	seconds_last = curTime.tv_sec;

	strftime(TimeString, 80, "%Y-%m-%d %H:%M:%S", localtime(&curTime.tv_sec));
}

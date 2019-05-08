/*
main.c

Aaron Knestaut
Maria van Venrooy
Cisc 210

Final Pi Project - Bop It
*/

#include "framebuffer.h"
#include <time.h>
#include <stdio.h>
#include <unistd.h>


//V Set pixel color
//framebuffer->bitmap->pixel[a][b] = getColor(0, 0, 0);
//V Pause for 1 second
//sleep(1);



void main(){

	pi_framebuffer_t* framebuffer = getFBDevice();
	
	int score = 0;
	int cont = 1;
	int task = 0;
	while(cont){
		clearBitmap(framebuffer->bitmap,getColor(0, 0, 0));
		
		//random number -> which task
		task = 
		
		//show color instruction
		//check for task completion
		//if task is failed, cont = 0
		//if task completed, score++


		
	}

	freeFrameBuffer(framebuffer);
	return 0;

	//display score
	showScore(score);
}

void showScore (int score)
{
	//display score
}


void allRed () {
	for (int i = 0; i < 8; i ++)
	{
		for (int j = 0; j < 8; j++)
		{
			framebuffer->bitap->pixel[i][j]= getColor(255,0,0);
		}
	}
}

void allGreen () {
        for (int i = 0; i < 8; i ++)
        {
                for (int j = 0; j < 8; j++)
                {
                        framebuffer->bitap->pixel[i][j]= getColor(0,255,0);
                }
        }
}

void allBlue () {
        for (int i = 0; i < 8; i ++)
        {
                for (int j = 0; j < 8; j++)
                {
                        framebuffer->bitap->pixel[i][j]= getColor(0,0,255);
                }
        }
}


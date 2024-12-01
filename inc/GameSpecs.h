#ifndef _GAMESPECS_H
#define _GAMESPECS_H


const int GRIDSIZE = 20;
const int HUMAN_STARTCOUNT = 100;
const int ZOMBIE_STARTCOUNT = 5;
const int HUMAN_BREED = 3; //num of steps
const int ZOMBIE_BREED = 8; // ''
const int ZOMBIE_STARVE = 3;
const char HUMAN_CH = 'H';
const char SPACE_CH = 45;
const char ZOMBIE_CH = 'Z';
const int INTERVAL = 500;
const int ITERATIONS = 1000; // max number of steps

//Colors
//0  = black				//9  = bright blue
//1  = blue					//10 = bright green
//2  = green				//11 = bright turquoise
//3  = turquoise				//12 = bright red
//4  = red					//13 = bright pink
//5  = pink					//14 = bright yellow
//6  = yellow				//15 = bright white
//7  = white regular		//16+ = solid blocks
//8  = white pale

const int HUMAN_COLOR = 3; // turquoise
const int ZOMBIE_COLOR = 14; // bright yellow
const int DASH_COLOR = 8; // pale white

#endif
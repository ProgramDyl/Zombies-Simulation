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
const std::string BRIGHT_GREEN = "\033[92m";
const std::string WHITE_PALE = "\033[97m";
const std::string TURQUOISE = "\033[36m";


//organism color assignments:
const std::string HUMAN_COLOR = TURQUOISE;
const std::string ZOMBIE_COLOR = BRIGHT_GREEN;
const std::string DASH_COLOR = WHITE_PALE;



#endif
#include "global.h"


// variables for global usage
int UNICORN_X = 0;
int UNICORN_Y = 0;

int BUILDING_X = 0;
int BUILDING_Y = 0;
int BUILDING2_X = 0;
int BUILDING2_Y = 0;
int BUILDING3_X = 0;
int BUILDING3_Y = 0;
int BUILDING4_X = 0;
int BUILDING4_Y = 0;

bool DIE = false;
bool DIE_key = true;
bool recovery = false;

int color_change = 250;
bool color_down = false;

float MOVING_SPEED = 8.5;
float SCORE = 1;
int HIGHEST_SCORE = 0;
int MAX_SCORE = 0;

bool BACK_TO_MENU = false;
bool CHECK_SLIDE = false;
bool RESTART_END = false;
bool BECOME_HORSE = false;
bool ABOUT_OR_START = false;

int MOVE_HINT = 1;

int RAND_DIST = 0;
const float FPS = 60.0;
const int WIDTH = 1000;
const int HEIGHT = 600;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *fps = NULL;
ALLEGRO_TIMER *fps_die = NULL;
bool key_state[ALLEGRO_KEY_MAX] = {false};
bool judge_next_window = false;
int windowChange = 1;
bool collide(int ux,int uy,int bx,int by){
    int distX = ux - bx;
    int distY = uy - by;
    int dist = sqrt(distX*distX + distY*distY);
    if(dist <= 80){
        return true;
    }else{
        return false;
    }
}

bool collide2(int ux,int uy,int bx,int by){
    int distX = ux - bx;
    int distY = uy - by;
    int dist = sqrt(distX*distX + distY*distY);
    //printf("dist:%d\n",dist);
    if(dist <= 80){
        return true;
    }else{
        return false;
    }
}

bool collide3(int ux,int uy,int bx,int by){
    int distX = ux - bx;
    int distY = uy - by;
    int dist = sqrt(distX*distX + distY*distY);
    //printf("dist:%d\n",dist);
    if(dist <= 65){
        return true;
    }else{
        return false;
    }
}

bool collide4(int ux,int uy,int bx,int by){
    int distX = ux - bx;
    int distY = uy - by;
    int dist = sqrt(distX*distX + distY*distY);
    //printf("dist:%d\n",dist);
    if(dist <= 50){
        return true;
    }else{
        return false;
    }
}
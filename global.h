#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED
#define GAME_TERMINATE -1
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// note that you can't assign initial value here!
extern const float FPS;
extern const int WIDTH;
extern const int HEIGHT;
extern bool key_state[ALLEGRO_KEY_MAX];
extern bool judge_next_window;
extern bool collide(int ux,int uy,int bx,int by);
extern bool collide2(int ux,int uy,int bx,int by);
extern bool collide3(int ux,int uy,int bx,int by);
extern bool collide4(int ux,int uy,int bx,int by);
extern int windowChange; 
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_TIMER *fps;
extern ALLEGRO_TIMER *fps_die;

extern int UNICORN_X;
extern int UNICORN_Y;

extern int BUILDING_X;
extern int BUILDING_Y;
extern int BUILDING2_X;
extern int BUILDING2_Y;
extern int BUILDING3_X;
extern int BUILDING3_Y;
extern int BUILDING4_X;
extern int BUILDING4_Y;

extern bool DIE;
extern bool DIE_key;
extern bool recovery;

extern float MOVING_SPEED;
extern float SCORE;
extern int HIGHEST_SCORE;
extern int MAX_SCORE;

extern int color_change;
extern bool color_down;

extern bool BACK_TO_MENU;
extern bool CHECK_SLIDE;
extern bool RESTART_END;
extern bool BECOME_HORSE;
extern bool ABOUT_OR_START;

extern int MOVE_HINT;

#endif

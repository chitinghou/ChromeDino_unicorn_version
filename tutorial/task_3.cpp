/*

GOAL:
Create a event_queue and make close window by the up right corner cross possible.

*/

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>     
#define GAME_TERMINATE 666


#define AL_INIT_FAILED -1
#define DESPLAY_INIT_FAILED -2

ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_EVENT_QUEUE* event_queue = NULL;
ALLEGRO_EVENT event;
/*
 * TODO: Declare your event_queue and event.
 */
int pos_x, pos_y;
const int width = 800;
const int height = 600;

const int gravity = 1;
int vely = 0;
int groundheight = 550;

bool key_state[ALLEGRO_KEY_MAX];
void show_err_msg(int msg);
void game_init();
void game_begin();
int process_event();
int game_run();
void game_destroy();
int keyboard_event();
int game_update();
void game_draw();
void jump();
void down();

int main(int argc, char *argv[]) {
    int msg = 0;

    game_init();
    game_begin();
    printf("Hello world!!!\n");
    printf("Close window to terminate.\n");

    while ( msg != GAME_TERMINATE ) {
        msg = game_run();
        if ( msg == GAME_TERMINATE )
            printf("See you, world\n");
    }
    game_destroy();
    return 0;
}

void show_err_msg(int msg) {
    fprintf(stderr, "unexpected msg: %d", msg);
    game_destroy();
    exit(9);
}

void game_init() {
    if ( !al_init() ) {
        show_err_msg(AL_INIT_FAILED);
    }
    pos_x = 50;
    pos_y = 50;

    display = al_create_display(width, height);
    al_set_window_position(display, 0, 0);
    event_queue = al_create_event_queue();
    if ( display == NULL ) {
        show_err_msg(DESPLAY_INIT_FAILED);
    }

    /*
     * TODO: initial display and event queue, and register specific event into event queue.
     */
     al_install_keyboard();
     al_init_primitives_addon();
     al_register_event_source(event_queue, al_get_keyboard_event_source());
}

void game_draw(){
    al_clear_to_color(al_map_rgb(0,0,0));
    vely += gravity;
    pos_y += vely;

    if(pos_y>=groundheight){
        pos_y = groundheight;
    }
    al_draw_filled_rectangle(pos_x, pos_y, pos_x + 30, pos_y + 30, al_map_rgb(255,200,255));
    al_flip_display();
}

void game_begin() {
    al_draw_filled_rectangle(100, 100, 10, 10, al_map_rgb(255,100,255));
    game_draw();
}

int process_event() {
    /*
     * TODO: Get the earliest event from event_queue and judge whether it represents the closing of window.
     *       If so, return GAME_TERMINATE.
     * Hint: using event.type == ALLEGRO_EVENT_DISPLAY_CLOSE to judge whether the display is closed just now.
     */
    al_wait_for_event(event_queue,&event);
    keyboard_event();
    int error = game_update();
    game_draw();
    return error;
}


int keyboard_event(){
    if(event.type == ALLEGRO_EVENT_KEY_DOWN){
        key_state[event.keyboard.keycode] = true;
    }else if(event.type == ALLEGRO_EVENT_KEY_UP){
        key_state[event.keyboard.keycode] = false;
    }
    return 0;
}

int game_update(){
    if( key_state[ALLEGRO_KEY_W] && pos_y >=groundheight-20){
        //pos_y -= 10;
        vely = -60;
        //jump();
    }else if( key_state[ALLEGRO_KEY_A] ){
        pos_x -= 10;
    }else if( key_state[ALLEGRO_KEY_S] ){
        pos_y += 10;
    }else if( key_state[ALLEGRO_KEY_D] ){
        pos_x += 10;
    }else if( key_state[ALLEGRO_KEY_ESCAPE] ){
        return GAME_TERMINATE;
    }else{
        vely = 0;
    }
    return 0;
}

void jump(){
    
}

int game_run() {
    /*
     * TODO: Judge whether there's any event in the queue; if so, call process_event() to process it.
     */
    int error = 0;
    if(!al_is_event_queue_empty(event_queue)){
        error = process_event();
    }
    game_draw();
    return error;
}

void game_destroy() {
    /*
     * TODO: Destroy all thing you have created.
     */
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
}

#include "charater.h"

const int gravity = 8;
int vely = 0;
int groundheight = 420;
ALLEGRO_BITMAP *img_rainbow;
// the state of character
enum {STOP = 0, MOVE, ATK, SLIDE, RAINBOW};
typedef struct character
{
    int x, y; // the position of image
    int width, height; // the width and height of image
    int sx,sy,sw,sh,dw,dh;
    bool dir; // left: false, right: true
    int state; // the state of character
    ALLEGRO_BITMAP *img_move[4];
    ALLEGRO_BITMAP *img_atk[2];
    ALLEGRO_SAMPLE_INSTANCE *magic_Sound;
    int anime; // counting the time of animation
    int anime_time; // indicate how long the animation
}Character;
Character chara;
ALLEGRO_SAMPLE *sample = NULL;
ALLEGRO_SAMPLE *jump_sample = NULL;
ALLEGRO_SAMPLE_INSTANCE *jump_sound = NULL;

ALLEGRO_SAMPLE *restart_sound_sample=NULL;
ALLEGRO_SAMPLE_INSTANCE *restart_sound;


int unicorn_getX(){return chara.sx;}
int unicorn_getY(){return chara.sy;}

void character_init(){
    img_rainbow = al_load_bitmap("./image/rainbow.png");
    // load character images
    for(int i = 1 ; i <= 4 ; i++){
        char temp[50];
        sprintf( temp, "./image/unicorn%d.png", i );
        //sprintf( temp, "./image/unicorn2.png");
        //chara.img_move[i-1] = al_load_bitmap(temp);
        chara.img_move[i-1] = al_load_bitmap(temp);
    }
    for(int i = 1 ; i <= 2 ; i++){
        char temp[50];
        sprintf( temp, "./image/unicorn%d.png", i );
        //sprintf( temp, "./image/unicorn2.png");
        chara.img_atk[i-1] = al_load_bitmap(temp);
    }
    // load effective sound
    sample = al_load_sample("./sound/magic.wav");
    chara.magic_Sound  = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(chara.magic_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(chara.magic_Sound, al_get_default_mixer());
    al_set_sample_instance_gain(chara.magic_Sound, 0.05) ;

    jump_sample = al_load_sample("./sound/jump.wav");
    jump_sound  = al_create_sample_instance(jump_sample);
    al_set_sample_instance_playmode(jump_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(jump_sound, al_get_default_mixer());

    restart_sound_sample = al_load_sample("./sound/option4.wav");
    restart_sound = al_create_sample_instance(restart_sound_sample);
    al_set_sample_instance_playmode(restart_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(restart_sound, al_get_default_mixer());
    al_set_sample_instance_gain(restart_sound, 0.3) ;

    // initial the geometric information of character
    chara.width = al_get_bitmap_width(chara.img_move[0]);
    chara.height = al_get_bitmap_height(chara.img_move[0]);
    chara.x = 40;
    chara.y = groundheight;
    chara.dir = false;
    //🦄add image size
    chara.sx = chara.sy = 0;
    chara.sw = chara.sh = 200;
    chara.dw = chara.dh = 150;

    // initial the animation component
    chara.state = MOVE;
    chara.anime = 0;
    chara.anime_time = 30;

    vely = 0;
}
void charater_process(ALLEGRO_EVENT event){
    // process the animation
    if( event.type == ALLEGRO_EVENT_TIMER ){
        if( event.timer.source == fps ){
            chara.anime++;
            chara.anime %= chara.anime_time;
        }
    // process the keyboard event
    }else if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
        key_state[event.keyboard.keycode] = true;
        chara.anime = 0;
    }else if( event.type == ALLEGRO_EVENT_KEY_UP ){
        key_state[event.keyboard.keycode] = false;
    }
}
void charater_update(){
    // use the idea of finite state machine to deal with different state
    if(!DIE){
        if( key_state[ALLEGRO_KEY_W] && chara.y >=(groundheight)){
        //chara.y -= 5;
        chara.state = STOP;
        al_play_sample_instance(jump_sound);
        vely = -150;
        }
        else if( key_state[ALLEGRO_KEY_S] ){
            //chara.y += 5;
            chara.state = SLIDE;
            if(key_state[ALLEGRO_KEY_W]){
                chara.state = RAINBOW;
            }
        }else if( chara.anime == chara.anime_time-1 ){
            chara.anime = 0;
            chara.state = MOVE;
        }else if ( chara.anime == 0 ){
            chara.state = MOVE;
        }else{
            vely = 0;
            chara.state = MOVE;
        }
    }else{
        // if(key_state[ALLEGRO_KEY_SPACE] ){
        //     //chara.state = ATK;
        //     printf("alive!\n");
        //     al_play_sample_instance(restart_sound);
        //     recovery = true;
        //     RESTART_END = false;
        //     printf("bad bad : 4\n");
        // }else if(key_state[ALLEGRO_KEY_ENTER]){
        //     al_play_sample_instance(restart_sound);
        //     recovery = true;
        //     RESTART_END = true;
        //     printf("bad bad : 5\n");
        // }else if(key_state[ALLEGRO_KEY_B]){
        //     BECOME_HORSE = true;
        // }else{
        //     printf("i even didn't touch the keyboard.\n");
        // }
    }

    vely += gravity;
    chara.y += vely;
    if(chara.y>=groundheight){
        chara.y = groundheight;
    }
    if(chara.y <= 0){
        chara.y = 0;
    }

    UNICORN_Y = chara.y;
    UNICORN_X = chara.x;
    if( chara.state == SLIDE ) CHECK_SLIDE = true;
    else CHECK_SLIDE = false;
    //printf("recover:%d\n",recovery);
}

int restart_anime;
int restart_anime_time;

void restart_init(){
    restart_anime = 0;
    restart_anime_time = 30;
}
void restart_process(ALLEGRO_EVENT event){
    // process the animation
    if( event.type == ALLEGRO_EVENT_TIMER ){
        if( event.timer.source == fps ){
            restart_anime++;
            restart_anime %= restart_anime_time;
        }
    // process the keyboard event
    }else if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
        key_state[event.keyboard.keycode] = true;
        restart_anime = 0;
    }else if( event.type == ALLEGRO_EVENT_KEY_UP ){
        key_state[event.keyboard.keycode] = false;
    }
}
void restart_update(){
    if(key_state[ALLEGRO_KEY_SPACE] ){
            //chara.state = ATK;
            printf("alive!\n");
            al_play_sample_instance(restart_sound);
            recovery = true;
            RESTART_END = false;
            //printf("bad bad : 4\n");
        }else if(key_state[ALLEGRO_KEY_ENTER]){
            al_play_sample_instance(restart_sound);
            recovery = true;
            RESTART_END = true;
            //printf("bad bad : 5\n");
        }else if(key_state[ALLEGRO_KEY_B]){
            BECOME_HORSE = true;
        }else{
            //printf("i even didn't touch the keyboard.\n");
    }
}

void character_draw(){
    // with the state, draw corresponding image
    if( chara.state == STOP ){
            al_draw_scaled_bitmap(chara.img_move[0], chara.sx, chara.sy, chara.sw, chara.sh, chara.x, chara.y,chara.dw, chara.dh, 0);
            
    }else if( chara.state == MOVE ){
        if( chara.anime < chara.anime_time/2 ){
            al_draw_scaled_bitmap(chara.img_move[0], chara.sx, chara.sy, chara.sw, chara.sh, chara.x, chara.y,chara.dw, chara.dh, 0);
        }else{
            al_draw_scaled_bitmap(chara.img_move[1], chara.sx, chara.sy, chara.sw, chara.sh, chara.x, chara.y,chara.dw, chara.dh, 0);
        }
    }else if( chara.state == SLIDE ){
        //printf("chara.state == SLIDE\n");
        if( chara.anime < chara.anime_time/2 ){
            al_draw_scaled_bitmap(chara.img_move[2], chara.sx, chara.sy, chara.sw, chara.sh, chara.x, chara.y,chara.dw, chara.dh, 0);
        }else{
            al_draw_scaled_bitmap(chara.img_move[3], chara.sx, chara.sy, chara.sw, chara.sh, chara.x, chara.y,chara.dw, chara.dh, 0);
        }
    }else if( chara.state == RAINBOW ){
            //al_draw_filled_rectangle(0,0,50,50,al_map_rgb(50,50,50));
            al_draw_bitmap(img_rainbow,80,120,0);
        if( chara.anime < chara.anime_time/2 ){
            al_draw_scaled_bitmap(chara.img_move[2], chara.sx, chara.sy, chara.sw, chara.sh, chara.x, chara.y,chara.dw, chara.dh, 0);
            al_play_sample_instance(chara.magic_Sound);
        }else{
            al_draw_scaled_bitmap(chara.img_move[3], chara.sx, chara.sy, chara.sw, chara.sh, chara.x, chara.y,chara.dw, chara.dh, 0);
            al_play_sample_instance(chara.magic_Sound);
        }
    }

}
void character_destory(){
    al_destroy_bitmap(chara.img_atk[0]);
    al_destroy_bitmap(chara.img_atk[1]);
    al_destroy_bitmap(chara.img_move[0]);
    al_destroy_bitmap(chara.img_move[1]);
    al_destroy_bitmap(chara.img_move[2]);
    al_destroy_bitmap(chara.img_move[3]);
    al_destroy_sample_instance(chara.magic_Sound);
    al_destroy_sample_instance(jump_sound);
    al_destroy_sample_instance(restart_sound);
}

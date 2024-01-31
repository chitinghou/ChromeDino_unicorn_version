#include "menuUnicorn.h"
// the state of character
enum {STOP = 0, MOVE, ATK, SELECT};
bool hint_lock = false;
ALLEGRO_SAMPLE *box_sound_sample=NULL;
ALLEGRO_SAMPLE_INSTANCE *box_sound;

ALLEGRO_SAMPLE *option_sound_sample=NULL;
ALLEGRO_SAMPLE_INSTANCE *option_sound;

ALLEGRO_SAMPLE *click_sound_sample=NULL;
ALLEGRO_SAMPLE_INSTANCE *click_sound;

ALLEGRO_FONT *hint_font = NULL;

typedef struct character
{
    int x, y; // the position of image
    int width, height; // the width and height of image
    bool dir; // left: false, right: true
    //bool about_start;
    int state; // the state of character
    ALLEGRO_BITMAP *img_move[3];
    ALLEGRO_BITMAP *img_atk[2];
    //ALLEGRO_BITMAP *img_select;
    ALLEGRO_SAMPLE_INSTANCE *atk_Sound;
    int anime; // counting the time of animation
    int anime_time; // indicate how long the animation
}Character;

Character unicorn_menu;
ALLEGRO_SAMPLE *sound_menu = NULL;
void menuUnicorn_init(){
    hint_font = al_load_ttf_font("./font/Amatic-Bold.ttf",25,0);
    
    box_sound_sample = al_load_sample("./sound/box.wav");
    box_sound = al_create_sample_instance(box_sound_sample);
    al_set_sample_instance_playmode(box_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(box_sound, al_get_default_mixer());
    al_set_sample_instance_gain(box_sound, 0.5) ;

    option_sound_sample = al_load_sample("./sound/option.wav");
    option_sound = al_create_sample_instance(option_sound_sample);
    al_set_sample_instance_playmode(option_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(option_sound, al_get_default_mixer());
    //al_set_sample_instance_gain(option_sound, 0.5) ;

    click_sound_sample = al_load_sample("./sound/option4.wav");
    click_sound = al_create_sample_instance(click_sound_sample);
    al_set_sample_instance_playmode(click_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(click_sound, al_get_default_mixer());
    al_set_sample_instance_gain(click_sound, 0.3) ;

    // load character images
    for(int i = 1 ; i <= 3 ; i++){
        char temp[50];
        sprintf( temp, "./image/unicornMenu%d.png", i );
        unicorn_menu.img_move[i-1] = al_load_bitmap(temp);
    }
    //unicorn_menu.img_select = al_load_bitmap("./image/unicornMenu4.png");
    // load effective sound
    sound_menu = al_load_sample("./sound/atk_sound.wav");
    unicorn_menu.atk_Sound  = al_create_sample_instance(sound_menu);
    al_set_sample_instance_playmode(unicorn_menu.atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(unicorn_menu.atk_Sound, al_get_default_mixer());

    // initial the geometric information of character
    unicorn_menu.width = al_get_bitmap_width(unicorn_menu.img_move[0]);
    unicorn_menu.height = al_get_bitmap_height(unicorn_menu.img_move[0]);
    unicorn_menu.x = -250;
    unicorn_menu.y = 0;
    unicorn_menu.dir = false;
    //unicorn_menu.about_start = false;

    // initial the animation component
    unicorn_menu.state = STOP;
    unicorn_menu.anime = 0;
    unicorn_menu.anime_time = 30;

}
void menuUnicorn_process(ALLEGRO_EVENT event){
    // process the animation
    if( event.type == ALLEGRO_EVENT_TIMER ){
        if( event.timer.source == fps ){
            unicorn_menu.anime++;
            unicorn_menu.anime %= unicorn_menu.anime_time;
        }
    // process the keyboard event
    }else if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
        key_state[event.keyboard.keycode] = true;
        unicorn_menu.anime = 0;
    }else if( event.type == ALLEGRO_EVENT_KEY_UP ){
        key_state[event.keyboard.keycode] = false;
    }
}
void menuUnicorn_update(){
    // use the idea of finite state machine to deal with different state
    if( key_state[ALLEGRO_KEY_W] ){
        unicorn_menu.state = SELECT;
        ABOUT_OR_START = true;
        al_play_sample_instance(option_sound);
    }
    if( key_state[ALLEGRO_KEY_A] )
    {
        unicorn_menu.dir = false;
        unicorn_menu.x -= 5;
        unicorn_menu.state = MOVE;
    }
    else if( key_state[ALLEGRO_KEY_S] ){
        
        unicorn_menu.state = SELECT;
        ABOUT_OR_START = false;
        al_play_sample_instance(option_sound);
    }
    else if( key_state[ALLEGRO_KEY_D] && unicorn_menu.x<=735) 
    {
        hint_lock = true;
        unicorn_menu.dir = true;
        unicorn_menu.x += 5;
        unicorn_menu.state = MOVE;
    }
    else if ( unicorn_menu.anime == 0 ){
        unicorn_menu.state = STOP;
        if(!hint_lock) MOVE_HINT++;
        //printf("MOVE_HINT:%d\n",MOVE_HINT);
    }
    else if(key_state[ALLEGRO_KEY_G] && ABOUT_OR_START==true){
            al_play_sample_instance(click_sound);
            windowChange = 2;
            //printf("bad bad : 1\n");
    }else if(key_state[ALLEGRO_KEY_ENTER] && ABOUT_OR_START==false){
            al_play_sample_instance(click_sound);
            windowChange = 4;
            //ABOUT_OR_START=true;
            //printf("bad bad : 2\n");
    }
    // else if(key_state[ALLEGRO_KEY_BACKSPACE] && unicorn_menu.about_start==false){
    //         al_play_sample_instance(click_sound);
    //         windowChange = 1;
    //         printf("bad bad : 3\n");
    // }
    else{
        unicorn_menu.state = STOP;
        //printf("hiiiiiii!\n");
    }
}


void menuUnicorn_draw(){
    // with the state, draw corresponding image
    if( unicorn_menu.state == STOP ){
        if((MOVE_HINT%2 == 1) && !hint_lock && MOVE_HINT>5) al_draw_text(hint_font, al_map_rgb(0,0,0), WIDTH/2+300, HEIGHT/2, ALLEGRO_ALIGN_RIGHT, "Press 'D'\n");
        if( ABOUT_OR_START )
            al_draw_bitmap(unicorn_menu.img_move[2], unicorn_menu.x, unicorn_menu.y, 0);
        else
            al_draw_bitmap(unicorn_menu.img_move[0], unicorn_menu.x, unicorn_menu.y, 0);
    }else if( unicorn_menu.state == MOVE ){
        al_play_sample_instance(box_sound);
        if( unicorn_menu.dir ){
            if( unicorn_menu.anime < unicorn_menu.anime_time/2 ){
                al_draw_bitmap(unicorn_menu.img_move[0], unicorn_menu.x, unicorn_menu.y, 0);
            }else{
                al_draw_bitmap(unicorn_menu.img_move[1], unicorn_menu.x, unicorn_menu.y, 0);
            }
        }else{
            if( unicorn_menu.anime < unicorn_menu.anime_time/2 ){
                al_draw_bitmap(unicorn_menu.img_move[0], unicorn_menu.x, unicorn_menu.y, 0);
            }else{
                al_draw_bitmap(unicorn_menu.img_move[1], unicorn_menu.x, unicorn_menu.y, 0);
            }
        }
    }else if( unicorn_menu.state == SELECT ){
        if( ABOUT_OR_START ){
            al_draw_bitmap(unicorn_menu.img_move[2], unicorn_menu.x, unicorn_menu.y, 0);
            }
        else{
            al_draw_bitmap(unicorn_menu.img_move[0], unicorn_menu.x, unicorn_menu.y, 0);
        }
    }
}
void menuUnicorn_destory(){
    al_destroy_font(hint_font);
    al_destroy_bitmap(unicorn_menu.img_atk[0]);
    al_destroy_bitmap(unicorn_menu.img_atk[1]);
    al_destroy_bitmap(unicorn_menu.img_move[0]);
    al_destroy_bitmap(unicorn_menu.img_move[1]);
    al_destroy_bitmap(unicorn_menu.img_move[2]);
    //al_destroy_bitmap(unicorn_menu.img_select);
    al_destroy_sample_instance(unicorn_menu.atk_Sound);
    al_destroy_sample_instance(box_sound);
    al_destroy_sample_instance(option_sound);
    al_destroy_sample_instance(click_sound);
}

int about_anime;
int about_anime_time;
void about_init(){
    about_anime = 0;
    about_anime_time = 30;
}
void about_process(ALLEGRO_EVENT event){
    // process the animation
    if( event.type == ALLEGRO_EVENT_TIMER ){
        if( event.timer.source == fps ){
            about_anime++;
            about_anime %= about_anime_time;
        }
    // process the keyboard event
    }else if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
        key_state[event.keyboard.keycode] = true;
        about_anime = 0;
    }else if( event.type == ALLEGRO_EVENT_KEY_UP ){
        key_state[event.keyboard.keycode] = false;
    }
}
void about_update(){
    // if(key_state[ALLEGRO_KEY_ENTER] && unicorn_menu.about_start==true){
    //         al_play_sample_instance(click_sound);
    //         windowChange = 2;
    //         printf("bad bad : 1\n");
    // }else if(key_state[ALLEGRO_KEY_ENTER] && unicorn_menu.about_start==false){
    //         al_play_sample_instance(click_sound);
    //         windowChange = 4;
    //         printf("bad bad : 2\n");
    // }else 
    if(key_state[ALLEGRO_KEY_BACKSPACE]){
            al_play_sample_instance(click_sound);
            ABOUT_OR_START=true;
            windowChange = 1;
            //printf("bad bad : 3\n");
    }
}
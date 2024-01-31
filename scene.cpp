#include "scene.h"
#include "menuUnicorn.h"

ALLEGRO_FONT *font = NULL;
ALLEGRO_FONT *restart_font = NULL;
ALLEGRO_FONT *restart_font2 = NULL;
ALLEGRO_FONT *restart_font3 = NULL;
ALLEGRO_BITMAP *menuBackground = NULL;
ALLEGRO_BITMAP *background = NULL;
ALLEGRO_BITMAP *restartBackground = NULL;
ALLEGRO_BITMAP *restartBackground2 = NULL;
ALLEGRO_BITMAP *aboutBackground = NULL;

ALLEGRO_SAMPLE *levelup_sound_sample=NULL;
ALLEGRO_SAMPLE_INSTANCE *levelup_sound;
float x=0;
int y=0;
char print_score[10];
char print_highest_score[10];
//int scene_move_speed = 8;
// function of menu
void menu_init(){
    menuUnicorn_init();
    font = al_load_ttf_font("./font/comic_zine_ot.otf",40,0);
    restart_font = al_load_ttf_font("./font/Amatic-Bold.ttf",50,0);
    restart_font2 = al_load_ttf_font("./font/Amatic-Bold.ttf",25,0);
    restart_font3 = al_load_ttf_font("./font/Amatic-Bold.ttf",70,0);
    menuBackground = al_load_bitmap("./image/unicornMenu.jpg");
    restartBackground = al_load_bitmap("./image/restartBackground2.jpg");
    restartBackground2 = al_load_bitmap("./image/restartBackground3.jpg");
    aboutBackground = al_load_bitmap("./image/about.jpg");

    levelup_sound_sample = al_load_sample("./sound/levelup.wav");
    levelup_sound  = al_create_sample_instance(levelup_sound_sample);
    al_set_sample_instance_playmode(levelup_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(levelup_sound, al_get_default_mixer());
    al_set_sample_instance_gain(levelup_sound, 0.3) ;
}
void menu_process(ALLEGRO_EVENT event){
    // if( event.type == ALLEGRO_EVENT_KEY_UP )
    //     if( event.keyboard.keycode == ALLEGRO_KEY_ENTER )
            //judge_next_window = true;
}
void menu_draw(){
    //al_clear_to_color(al_map_rgb(200,100,100));
    al_draw_bitmap(menuBackground,0,0,0);
    //al_draw_rectangle(WIDTH/2-150, 510, WIDTH/2+150, 550, al_map_rgb(25, 25, 25), 0);
    menuUnicorn_draw();
}
void menu_destroy(){
    al_destroy_font(font);
    al_destroy_bitmap(menuBackground);
    menuUnicorn_destory();
}

// function of game_scene
void game_scene_init(){
    character_init();
    building_init();
    background = al_load_bitmap("./image/runBackground4.png");
}
void game_scene_draw(){
    x -= MOVING_SPEED;
    SCORE+=0.1;
    if((int)SCORE%100 == 0){
        MOVING_SPEED+=0.2;
        al_play_sample_instance(levelup_sound);
        //printf("MOVING_SPEED: %f\n",MOVING_SPEED);
    }
    
    
    if(color_change >= 250 && (int)SCORE%200 == 0) color_down = true;
    if(color_change <= 10 && (int)SCORE%200 == 0) color_down = false;
    if(color_down && color_change>=10) color_change--;
    else if(!color_down && color_change <= 250) color_change++;
    al_draw_filled_rectangle(0,0,al_get_bitmap_width(background),al_get_bitmap_height(background),al_map_rgb(color_change,color_change,color_change));

    if(x< - WIDTH)x=0;
    al_draw_scaled_bitmap(background, 0, 0,al_get_bitmap_width(background),al_get_bitmap_height(background),x,y,WIDTH,HEIGHT,0);
    al_draw_scaled_bitmap(background, 0, 0,al_get_bitmap_width(background),al_get_bitmap_height(background),WIDTH+x,y,WIDTH,HEIGHT,0);
    //al_draw_bitmap(background, 0, 0, 0);
    character_draw();
    building_draw();

    sprintf(print_score, "%05d",(int)SCORE);
    sprintf(print_highest_score, "%05d",HIGHEST_SCORE);
    if(color_down == true){
        al_draw_text(font, al_map_rgb(250,250,250), WIDTH-60, 10 , ALLEGRO_ALIGN_CENTRE, print_score);
    }
    else{
        al_draw_text(font, al_map_rgb(0,0,0), WIDTH-60, 10 , ALLEGRO_ALIGN_CENTRE, print_score);
        
    }
    al_draw_text(font, al_map_rgb(150,150,150), WIDTH-250, 10 , ALLEGRO_ALIGN_CENTRE, "HI ");
    al_draw_text(font, al_map_rgb(150,150,150), WIDTH-180, 10 , ALLEGRO_ALIGN_CENTRE, print_highest_score);
    //heidi debug
    //printf("score:%f\n",score);

    //al_flip_display();

}
void game_scene_destroy(){
    al_destroy_font(font);
    //al_destroy_font(restart_font);
    //al_destroy_bitmap(menuBackground);
    al_destroy_bitmap(background);
    character_destory();
    building_destory();
    
}

void restart_scene_draw(){
    //if(DIE && !DIE_key){
        //printf("restart_scene_draw \n");
        if(BECOME_HORSE) al_draw_bitmap(restartBackground2,0,0,0);
        else al_draw_bitmap(restartBackground,0,0,0);
        al_draw_text(restart_font2, al_map_rgb(0,0,0), 50, 90 , ALLEGRO_ALIGN_LEFT, "'space' to restart\n");
        al_draw_text(restart_font2, al_map_rgb(0,0,0), 50, 130 , ALLEGRO_ALIGN_LEFT, "'enter' to end\n");
        al_draw_text(restart_font2, al_map_rgb(0,0,0), 50, 170 , ALLEGRO_ALIGN_LEFT, "'b' to tint\n");
        al_draw_text(font, al_map_rgb(0,0,0), WIDTH-60, 10 , ALLEGRO_ALIGN_CENTRE, print_score);
        al_draw_text(restart_font, al_map_rgb(0,0,0), WIDTH/2-30, HEIGHT/2-20 , ALLEGRO_ALIGN_CENTRE, "Well done!");
        al_draw_text(restart_font, al_map_rgb(0,0,0), WIDTH/2-30, HEIGHT/2+40 , ALLEGRO_ALIGN_CENTRE, "A unicorn loses its horn and becomes a horse.");
    //}
}
void restart_scene_destroy(){
    al_destroy_font(font);
    al_destroy_bitmap(restartBackground);
    al_destroy_bitmap(restartBackground2);
    al_destroy_font(restart_font);
    al_destroy_font(restart_font2);
}


void about_scene_draw(){
    //if(DIE && !DIE_key){
        //printf("restart_scene_draw \n");
        al_draw_bitmap(aboutBackground,0,0,0);
        //al_draw_filled_rectangle(0,0,al_get_bitmap_width(background),al_get_bitmap_height(background),al_map_rgb(250,250,250));
        //al_draw_text(font, al_map_rgb(0,0,0), WIDTH-60, 10 , ALLEGRO_ALIGN_CENTRE, print_score);
        al_draw_text(restart_font2, al_map_rgb(0,0,0), 80, 90 , ALLEGRO_ALIGN_LEFT, "backspace!\n");
        al_draw_text(restart_font3, al_map_rgb(0,0,0), WIDTH/2-40, 40 , ALLEGRO_ALIGN_LEFT, "rules\n");
        al_draw_text(restart_font, al_map_rgb(0,0,0), 210, 180 , ALLEGRO_ALIGN_LEFT, "1. Unicorns are real !\n");
        al_draw_text(restart_font, al_map_rgb(0,0,0), 210, 245 , ALLEGRO_ALIGN_LEFT, "2. Key press only\n");
        al_draw_text(restart_font, al_map_rgb(0,0,0), 210, 305 , ALLEGRO_ALIGN_LEFT, "3. Pressing ‘W’ will jump, and ‘S’ will duck\n");
        al_draw_text(restart_font, al_map_rgb(0,0,0), 210, 370 , ALLEGRO_ALIGN_LEFT, "4. Pressing ‘S’ + ‘W’ will ???\n");
        //al_draw_text(restart_font, al_map_rgb(0,0,0), WIDTH/2-30, HEIGHT/2-20 , ALLEGRO_ALIGN_CENTRE, "Press Enter to Go home!");
    //}
}
void about_scene_destroy(){
    al_destroy_font(restart_font);
    al_destroy_font(restart_font2);
    al_destroy_font(restart_font3);
    al_destroy_bitmap(aboutBackground);
}
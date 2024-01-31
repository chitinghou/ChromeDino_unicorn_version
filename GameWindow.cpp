#include "GameWindow.h"

bool draw = false;

const char *title = "The origin of the horse";

// ALLEGRO Variables
ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_SAMPLE *song=NULL;
ALLEGRO_SAMPLE_INSTANCE *sample_instance;

ALLEGRO_SAMPLE *death_sound_sample=NULL;
ALLEGRO_SAMPLE_INSTANCE *death_sound;

int Game_establish() {
    int msg = 0;

    game_init();
    game_begin();

    while ( msg != GAME_TERMINATE ) {
        msg = game_run();
        if ( msg == GAME_TERMINATE )
            printf( "Game Over\n" );
    }

    game_destroy();
    return 0;
}

void game_init() {
    printf( "Game Initializing...\n" );
    al_init();
    // init audio
    al_install_audio();
    al_init_acodec_addon();
    // Create display
    display = al_create_display(WIDTH, HEIGHT);
    // create event queue
    event_queue = al_create_event_queue();
    // Initialize Allegro settings
    al_set_window_position(display, 0, 200);
    al_set_window_title(display, title);
    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon
    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event
    // Register event
    al_register_event_source(event_queue, al_get_display_event_source( display ));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    fps  = al_create_timer( 1.0 / FPS );
    al_register_event_source(event_queue, al_get_timer_event_source( fps )) ;

    // fps_die  = al_create_timer( 1.0 / 6000 );
    // al_register_event_source(event_queue, al_get_timer_event_source( fps_die )) ;

    // initialize the icon on the display
    ALLEGRO_BITMAP *icon = al_load_bitmap("./image/unicorn1.png");

    BECOME_HORSE = false;
}

void game_begin() {
    // Load sound
    song = al_load_sample("./sound/game_bgm.wav");

    al_reserve_samples(20);
    sample_instance = al_create_sample_instance(song);

    // Loop the song until the display closes
    al_set_sample_instance_playmode(sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(sample_instance, al_get_default_mixer());

    // set the volume of instance
    al_set_sample_instance_gain(sample_instance, 1) ;
    al_play_sample_instance(sample_instance);

    death_sound_sample = al_load_sample("./sound/death.wav");
    death_sound = al_create_sample_instance(death_sound_sample);
    al_set_sample_instance_playmode(death_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(death_sound, al_get_default_mixer());


    al_start_timer(fps);
    // initialize the menu before entering the loop
    menu_init();
    game_scene_init();
    about_init();
    restart_init();

}
void game_update(){
    //if( !judge_next_window ){
    if( windowChange == 1 ){
        //printf("yesssssssss\n");
        menuUnicorn_update();
        // not back menu anymore, therefore destroy it
        //menu_destroy();

        // initialize next scene
        // game_scene_init();
        // judge_next_window = false;
        // window = 2;
    }
    //}
    if( windowChange == 2 ){
        recovery = false;
        //printf("window update \n");
        charater_update();
        building_update();
        //heidi debug
        //printf("ux:%d, uy:%d, bx:%d, by:%d\n", get_unicornX, get_unicornY,get_buildingX, get_buildingY);
        int get_UNICORN_X = UNICORN_X + 75;
        int get_UNICORN_Y = UNICORN_Y + 75;
        int get_BUILDING_X = BUILDING_X + 25;
        int get_BUILDING_Y = BUILDING_Y + 25;
        int get_BUILDING2_X = BUILDING2_X + 23;
        int get_BUILDING2_Y = BUILDING2_Y + 41;
        int get_BUILDING3_X = BUILDING3_X + 12;
        int get_BUILDING3_Y = BUILDING3_Y + 30;
        int get_BUILDING4_X = BUILDING4_X + 20;
        int get_BUILDING4_Y = BUILDING4_Y + 30;
        if(collide(get_UNICORN_X, get_UNICORN_Y,get_BUILDING_X, get_BUILDING_Y) && DIE_key){
            //heidi debug
            printf("-----------------collide-----------------\n");
            DIE = true;
            DIE_key = false;
            al_play_sample_instance(death_sound);
            al_stop_sample_instance(sample_instance);
            
        }

        if(collide2(get_UNICORN_X, get_UNICORN_Y,get_BUILDING2_X, get_BUILDING2_Y) && DIE_key){
            //heidi debug
            printf("-----------------collide-----------------\n");
            DIE = true;
            DIE_key = false;
            al_play_sample_instance(death_sound);
            al_stop_sample_instance(sample_instance);
            
        }

        if(collide3(get_UNICORN_X, get_UNICORN_Y,get_BUILDING3_X, get_BUILDING3_Y) && DIE_key){
            //heidi debug
            printf("-----------------collide-----------------\n");
            DIE = true;
            DIE_key = false;
            al_play_sample_instance(death_sound);
            al_stop_sample_instance(sample_instance);
            
        }

        if(collide4(get_UNICORN_X, get_UNICORN_Y,get_BUILDING4_X, get_BUILDING4_Y) && DIE_key){
            //heidi debug
            printf("-----------------collide-----------------\n");
            DIE = true;
            DIE_key = false;
            al_play_sample_instance(death_sound);
            al_stop_sample_instance(sample_instance);
            
        }

        if(DIE && !DIE_key){
            //al_start_timer(fps_die);
            windowChange = 3;
            if(SCORE > HIGHEST_SCORE) HIGHEST_SCORE = SCORE;
        }
    }
    if( windowChange == 3 ){
        recovery = false;
        //charater_update();
        //building_update();
        restart_update();
        if(DIE_key == false && recovery == true){
                about_scene_destroy();
                game_scene_destroy();
                al_destroy_event_queue(event_queue);
                al_destroy_display(display);
                printf("inside recovery \n");
                game_init();
                game_begin();
                BUILDING_X = BUILDING_Y = BUILDING2_X = BUILDING2_Y = BUILDING3_X = BUILDING3_Y = BUILDING4_X = BUILDING4_Y = 0;
                SCORE = 1;
                MOVING_SPEED = 8.5;
                color_change = 250;
                color_down = false;
                DIE_key = true;
                recovery = false;
                DIE = false;
                CHECK_SLIDE = false;
                ABOUT_OR_START=true;
                if(RESTART_END) windowChange = 1;
                else windowChange = 2;
                RESTART_END = false;
        }
    }
    if( windowChange == 4 ){
        //menuUnicorn_update();
        about_update();
        //printf("noooooooo\n");
    }
}
int process_event(){
    // Request the event
    ALLEGRO_EVENT event;
    al_wait_for_event(event_queue, &event);
    // process the event of other component
    if( windowChange == 1 ){
        menu_process(event);
        menuUnicorn_process(event);
    }else if( windowChange == 2 ){
        charater_process(event);
        building_process(event);
    }else if( windowChange == 3 ){
        //charater_process(event);
        //building_process(event);
        restart_process(event);
    }else if( windowChange == 4 ){
        about_process(event);
    }

    // Shutdown our program
    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        return GAME_TERMINATE;
    else if(event.type == ALLEGRO_EVENT_TIMER)
        if(event.timer.source == fps)
            draw = true;
    game_update();
    return 0;
}
void game_draw(){
    if( windowChange == 1 ){
        menu_draw();
    }else if( windowChange == 2 && !DIE) {
        game_scene_draw();
    }else if( windowChange == 3 ){
        restart_scene_draw();
    }else if( windowChange == 4 ){
        about_scene_draw();
    }
    al_flip_display();
}
int game_run() {
    //printf("%d\n",window);
    int error = 0;
    if( draw ){
        game_draw();
        draw = false;
    }
    // if(DIE){
    //     restart_scene_draw();
    //     al_flip_display();
    // }
    if ( !al_is_event_queue_empty(event_queue) ) {
        error = process_event();
    }
    return error;
}

void game_destroy() {
    // Make sure you destroy all things
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
    game_scene_destroy();
    // about_scene_destroy();
    // restart_scene_destroy();
}

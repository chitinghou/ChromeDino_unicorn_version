#include "building.h"

int building_groundheight = 500;
int building_start = WIDTH;
//int building_move_speed = 8;  //same as scene moving speed

typedef struct Building
{
    int x, y; // the position of image
    int width, height; // the width and height of image
    bool dir; // left: false, right: true
    int state; // the state of character
    ALLEGRO_BITMAP *img_building;
    int anime; // counting the time of animation
    int anime_time; // indicate how long the animation
    float building_move;
}Building;
Building building1;
Building building2;
Building building3;
Building building4;

void building_init(){
    building1.img_building = al_load_bitmap("./image/build1.png");
    building1.x = building_start ;
    building1.y = building_groundheight ;
    building1.building_move=0;

    int rand_start_pos;
    srand(time(NULL));
    rand_start_pos = ((rand()%5)+2)*100;
    //heidi debug
    //printf("rand_start_pos:%d\n",rand_start_pos);

    building2.img_building = al_load_bitmap("./image/build2.png");
    building2.x = building_start + rand_start_pos ;
    building2.y = building_groundheight - 30;
    building2.building_move=0;

    int rand_start_pos2;
    srand(time(NULL));
    rand_start_pos2 = ((rand()%8)+4)*100;
    //heidi debug
    //printf("rand_start_pos2:%d\n",rand_start_pos2);

    building3.img_building = al_load_bitmap("./image/light.png");
    building3.x = building_start + rand_start_pos2 ;
    building3.y = building_groundheight;
    building3.building_move=0;

    int rand_start_pos3;
    srand(time(NULL));
    rand_start_pos3 = ((rand()%5)+2)*100;
    //heidi debug
    //printf("rand_start_pos3:%d\n",rand_start_pos3);

    building4.img_building = al_load_bitmap("./image/airplane.png");
    building4.x = building_start + rand_start_pos2 + rand_start_pos3;
    building4.y = building_groundheight - 30;
    building4.building_move=0;
 }
void building_process(ALLEGRO_EVENT event){

}
void building_update(){
    
}
void building_draw(){
    //al_draw_bitmap(building1.img_building, building1.x, building1.y, 0);
    int rand_dist;
    srand(time(NULL));
    rand_dist = ((rand()%50)+1)*100;
    //heidi debug
    building1.building_move -= MOVING_SPEED;
    if(building1.building_move < - WIDTH - rand_dist) building1.building_move=0;
    al_draw_bitmap(building1.img_building, building1.x + building1.building_move, building1.y, 0);
    //printf("building1:%d\n",a);

    BUILDING_Y = building1.y;
    BUILDING_X = building1.x + building1.building_move;
    //heidi debug
    //printf("bulding1_x: %d\n",BUILDING_X);


    int rand_dist2;
    srand(time(NULL));
    rand_dist2 = ((rand()%300)+60)*10;
    //heidi debug
    //printf("-------rand:%d\n",rand_dist2);
    building2.building_move -= MOVING_SPEED;
    //printf("-----------building2:%d\n",b);
    if(building2.building_move < - WIDTH - rand_dist2) building2.building_move=0;
    //if((b-a)<300) building2.building_move=0;
    al_draw_bitmap(building2.img_building, building2.x + building2.building_move, building2.y, 0);

    BUILDING2_Y = building2.y;
    BUILDING2_X = building2.x + building2.building_move;

    //printf("building2 - building1:%d\n",b-a);

    int rand_dist3;
    srand(time(NULL));
    rand_dist3 = ((rand()%200)+100)*10;
    //heidi debug
    //printf("-------rand:%d\n",rand_dist2);
    building3.building_move -= MOVING_SPEED;
    //printf("-----------building2:%d\n",b);
    if(building3.building_move < - WIDTH - rand_dist3) building3.building_move=0;
    //if((b-a)<300) building2.building_move=0;
    al_draw_bitmap(building3.img_building, building3.x + building3.building_move, building3.y, 0);
    BUILDING3_Y = building3.y;
    BUILDING3_X = building3.x + building3.building_move;


    int rand_dist4;
    srand(time(NULL));
    rand_dist4 = ((rand()%300)+150)*10;
    //heidi debug
    //printf("-------rand:%d\n",rand_dist2);
    building4.building_move -= MOVING_SPEED;
    //printf("-----------building2:%d\n",b);
    if(building4.building_move < - WIDTH - rand_dist4) building4.building_move=0;
    //if((b-a)<300) building2.building_move=0;
    al_draw_bitmap(building4.img_building, building4.x + building4.building_move, building4.y, 0);
    if(CHECK_SLIDE){
        BUILDING4_Y = building4.y + 150;
    }else{
        BUILDING4_Y = building4.y;
    }
    //printf("BUILDING4_Y:%d\n",BUILDING4_Y);
    BUILDING4_X = building4.x + building4.building_move;
    
}
void building_destory(){
    al_destroy_bitmap(building1.img_building);
    al_destroy_bitmap(building2.img_building);
    al_destroy_bitmap(building3.img_building);
    al_destroy_bitmap(building4.img_building);
}

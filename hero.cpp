#include"hero.hpp"


Hero::Hero(){
  pos_x = 10.0f;
  pos_y = 450.0f;
  width = 50;
  height = 50;
}

Hero::~Hero(){

}

//jump
void Hero::Jump(){
  //set dt
  previousTime = currentTime;
  currentTime = GetTime();
  float dt = currentTime - previousTime;
  //float dt =0.15f;
  //printf("dt: %f\n",dt);
  float scalingfactor  =5.0f;
  pos_y -= velocity_y*dt*scalingfactor;
  pos_x += velocity_x*dt*scalingfactor;
  
  velocity_y += gravity*dt*scalingfactor;
  
  //printf("posy: %f\n",pos_y);
  //printf("velocity_y: %f\n",velocity_y);

  if(pos_y > 450.0f){
    pos_y = 450.0f;
    IsJumping = false;
    velocity_y = 100.0f;
    velocity_x = 0.0f;
  }
}
//move
void Hero::Move(int dir){
  if(IsJumping){
    switch(dir){
    case 3://east
      velocity_x = 30.0f;break;
    case 4://west
      velocity_x = -30.0f;break;
    default:
      velocity_x = 0.0f;
      break;
    }
  }else if(!IsJumping){
    switch(dir){
    case 3:
      pos_x += 10.0f;break;
    case 4:
      pos_x -= 10.0f;break;
    }
  }
    
}
void Hero::Draw(){
  DrawRectangle(pos_x,pos_y,width,height,GREEN);
}

//drop the hero down
void Hero::DropDown(float dt){
  //printf("dt: %f\n",dt);
  printf("In drop down\n");
  float scalingfactor  =5.0f;
  pos_y -= down_velo*dt*scalingfactor;
  
  down_velo += gravity*dt*scalingfactor;
}

void Hero::Update(){
  
}

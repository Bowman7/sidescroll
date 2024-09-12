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
  if(!LandedYet){
    startTime = GetTime();
    LandedYet = true;
  }
  float gravity = -0.5f;
  float velocity = 2.0f;
  float currentTime = GetTime();
  float time = startTime - currentTime;

  pos_y -= gravity*time*time+velocity*time;
  
}
//move
void Hero::Move(int dir){
  switch(dir){
  case 1://north
    pos_y-=5.0f;break;
  case 2://south
    pos_y+=5.0f;break;
  case 3://east
    pos_x+=10.0f;break;
  case 4://west
    pos_x-=10.0f;break;
  default:
    break;
  }
    
}
void Hero::Draw(){
  DrawRectangle(pos_x,pos_y,width,height,GREEN);
}

void Hero::Update(){
  if(pos_y >450.0f && IsJumping== true){
    IsJumping = false;
    pos_y = 450.0f;
    LandedYet = false;
  }
}

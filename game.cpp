#include"game.hpp"


Game::Game(int width,int height){
  Width = width;
  Height = height;

  //init platforms
  InitPlatformPos();
}

Game::Game(){
  
}

Game::~Game(){

}

void Game::DrawGround(){
  DrawLine(0,p_height,Width,p_height,BLACK);
}
//innit platform pos
void Game::InitPlatformPos(){
  platform.SetXY(200,300);
}
//check collision between payer and platform
void Game::CheckCollision(){
  
}
void Game::Draw(){
  //draw ground
  DrawGround();
  //drwa the platforms
  platform.Draw();
  //draw player
  hero.Draw();
  DrawRectangle(0,0,100,100,PINK);
}

void Game::Update(float time){
  float currentTime = time;
  //up hero
  hero.Update();
  //set jump
  if(hero.GetIsJumping()){
    hero.Jump();
    //check col
    CheckCollision();
  }else if(hero.InAir() && !hero.GetIsJumping()){//check if in air
    hero.DropDown(currentTime);
    //check collision
    CheckCollision();
  }

  

 
}

void Game::HandleInput(){
  //check inputs
  if(IsKeyDown(KEY_D)){
    hero.Move(3);//east
  }
  if(IsKeyDown(KEY_A)){
    hero.Move(4);//west
  }
  if(IsKeyPressed(KEY_SPACE)){
    if(hero.GetIsJumping() == false){
      hero.SetJumpTrue();
    }
  }
  if(IsKeyPressed(KEY_W)){
    hero.SetY(200.0f);
  }
}

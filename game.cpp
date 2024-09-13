#include"game.hpp"


Game::Game(int width,int height){
  Width = width;
  Height = height;
}

Game::Game(){
  
}

Game::~Game(){

}

void Game::DrawPlatform(){
  DrawLine(0,p_height,Width,p_height,BLACK);
}

void Game::Draw(){
  //draw platform
  DrawPlatform();
  //draw player
  hero.Draw();
}

void Game::Update(){
  //up hero
  hero.Update();
  //set jump
  if(hero.GetIsJumping()){
    hero.Jump();
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
  if(IsKeyDown(KEY_SPACE)){
    if(hero.GetIsJumping() == false){
      hero.SetJumpTrue();
    }
  }
}

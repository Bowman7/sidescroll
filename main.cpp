#include"raylib.h"

#define HEIGHT 720
#define WIDTH  1072

#include"game.hpp"
#include"core.hpp"
#include<string>

enum core_state{
  STARTSCREEN = 0,
  GAMEPLAY,
  ENDSCREEN,
  WON
};
int main(){
  
  //init window
  InitWindow(WIDTH,HEIGHT,"window");

  SetTargetFPS(60);
  //init audio device
  InitAudioDevice();

  float prevTime = 0.0f;
  float currentTime = GetTime();
  //setup game object
  Game game(WIDTH,HEIGHT);
  
  //core game
  //setup camera
  Camera2D camera ={0};
  Core core(camera);
  //state
  core_state c_state = STARTSCREEN;

  Music music;
  Sound select;
  Sound s_won;
  Sound s_lost;
  
 
  
  select = LoadSound("music/select-sound.mp3");
  music = LoadMusicStream("music/cave.mp3");
  s_won = LoadSound("music/level-win.mp3");
  s_lost = LoadSound("music/gameover.wav");
  
  
  while(!WindowShouldClose()){
    //update musc
    UpdateMusicStream(music);
    //delat time
    prevTime = currentTime;
    currentTime = GetTime();
    float dt = currentTime - prevTime;
	
    switch(c_state){
    case STARTSCREEN:
      {
	core.GameInit();
	if(IsKeyPressed(KEY_ENTER)){
	  PlaySound(select);
	  c_state = GAMEPLAY;
	}
      }break;
    case GAMEPLAY:
      {
	PlayMusicStream(music);
	//handle input
	core.HandleInput(dt);
	//update
	core.Update(dt,camera);
	//check for gamewon
	if(core.IsGameWon()){
	  StopMusicStream(music);
	  PlaySound(s_won);
	  c_state = WON;
	}
	if(core.IsGameOver()){
	  StopMusicStream(music);
	  PlaySound(s_lost);
	  c_state = ENDSCREEN;
	}
      }break;
    case ENDSCREEN:
      {
	if(IsKeyPressed(KEY_ENTER)){
	  PlaySound(select);
	  c_state  = STARTSCREEN;
	}
      }break;
    case WON:
      {
	if(IsKeyPressed(KEY_ENTER)){
	  PlaySound(select);
	  c_state = STARTSCREEN;
	}
      }break;
    }
   
    //draw
    BeginDrawing();
    ClearBackground(BLACK);
    switch(c_state){
    case STARTSCREEN:
      {
	DrawRectangle(0,0,1080,720,BLACK);
	DrawText("Press Enter!",360,360,50,WHITE);
	DrawText("WASD : Up,Left,Down,Right",360,400,50,WHITE);
	DrawText("Space: Jump",360,440,50,WHITE);
      }break;
    case GAMEPLAY:
      {
	BeginMode2D(camera);
	
	core.Draw(camera);
	//DrawText("yeay",200,200,20,BLACK);
	
	EndMode2D();
	core.DrawHealth();
      }break;
    case ENDSCREEN:
      {
	DrawText("YOU DIED!",360,360,50,WHITE);
	DrawText("Press Enter!",400,500,25,WHITE);
      }break;
    case WON:
      {
	DrawText("YOU ESCAPED!",360,360,50,WHITE);
	DrawText("Press Enter!",450,500,25,WHITE);
      }break;
      
    }
   
    EndDrawing();
  }

  CloseWindow();

  return 0;
}

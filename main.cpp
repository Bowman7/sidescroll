#include"raylib.h"

#define HEIGHT 1000
#define WIDTH  1000

#include"game.hpp"
#include"core.hpp"
#include<string>

int main(){
  
  //init window
  InitWindow(WIDTH,HEIGHT,"window");

  SetTargetFPS(60);

  float prevTime = 0.0f;
  float currentTime = GetTime();
  //setup game object
  Game game(WIDTH,HEIGHT);

  //core game
  Core core;
  while(!WindowShouldClose()){
    //delat time
    prevTime = currentTime;
    currentTime = GetTime();
    float dt = currentTime - prevTime;

    //handle input
    core.HandleInput();
    //update
    core.Update(dt);

    //draw
    BeginDrawing();
    ClearBackground(WHITE);

    core.Draw();
    //DrawText("yeay",200,200,20,BLACK);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}

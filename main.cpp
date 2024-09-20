#include"raylib.h"

#define HEIGHT 800
#define WIDTH  800

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
  //setup camera
  Camera2D camera ={0};
  Core core(camera);
  
  
  while(!WindowShouldClose()){
    //delat time
    prevTime = currentTime;
    currentTime = GetTime();
    float dt = currentTime - prevTime;

    //handle input
    core.HandleInput(dt);
    //update
    core.Update(dt,camera);

    //draw
    BeginDrawing();
    ClearBackground(WHITE);
    BeginMode2D(camera);

    core.Draw(camera);
    //DrawText("yeay",200,200,20,BLACK);

    EndMode2D();
    EndDrawing();
  }

  CloseWindow();

  return 0;
}

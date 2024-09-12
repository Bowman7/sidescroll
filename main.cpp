#include"raylib.h"

#define HEIGHT 720
#define WIDTH 1080

#include"game.hpp"

int main(){
  
  //init window
  InitWindow(WIDTH,HEIGHT,"window");

  SetTargetFPS(60);

  //setup game object
  Game game(WIDTH,HEIGHT);
  while(!WindowShouldClose()){
    //handle input
    game.HandleInput();
    //update
    game.Update();

    //draw
    BeginDrawing();
    ClearBackground(WHITE);

    game.Draw();
    DrawText("yeay",200,200,20,BLACK);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}

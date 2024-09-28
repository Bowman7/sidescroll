#include"raylib.h"

#include<stdio.h>

#include"hero.hpp"
#include"platform.hpp"

class Game{
public:
  Game();
  Game(int,int);
  ~Game();
  void GameMain();
  void Draw();
  void Update(float);
  void HandleInput();

  void DrawGround();
  void InitPlatformPos();

  //collision
  void CheckCollision();
private:
  Hero hero;
  Platform platform;

  
  
  int Width;
  int Height;
  int p_height = 500;

};

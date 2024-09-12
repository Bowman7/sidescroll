#include"raylib.h"

#include"hero.hpp"

class Game{
public:
  Game();
  Game(int,int);
  ~Game();
  void Draw();
  void Update();
  void HandleInput();

  void DrawPlatform();
private:
  Hero hero;
  
  int Width;
  int Height;
  int p_height = 500;
};

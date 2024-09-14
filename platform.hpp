#include"raylib.h"

class Platform{
public:
  Platform(){}
  ~Platform(){}
  void Draw();
  void SetXY(int x,int y){
    posX = x;
    posY = y;
  }
  int GetX(){
    return posX;
  }
  int GetY(){
    return posY;
  }
  int GetWidth(){
    return width;
  }
  int GetHeight(){
    return height;
  }
  void SetColor(){
    color = BLUE;
  }
  void SetBackColor(){
    color = RED;
  }

private:
  int posX;
  int posY;
  int width = 100;
  int height = 25;
  Color color = RED;
};

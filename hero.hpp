#include"raylib.h"
#include<stdio.h>
#include<math.h>

class Hero{
public:
  Hero();
  ~Hero();

  void Draw();
  void Update();

  void Move(int);
  void SetJumpTrue(){
    IsJumping = true;
    currentTime = GetTime();
  }
  bool GetIsJumping(){
    return IsJumping;
  }
  void SetJumpFalse(){
    IsJumping = false;
    velocity_y = 100.0f;
    velocity_x =0.0f;
  }
  void Jump();

  int GetX(){
    return (int)pos_x;
  }
  

  int GetY(){
    return (int)pos_y;
  }
  int GetWidth(){
    return width;
  }
  int GetHeight(){
    return height;
  }

  void SetX(int x){
    pos_x =(float)x;
  }
  void SetY(int y){
    pos_y =(float)y;
  }
  void SetOppositeDir(){
    velocity_y *= -1;
  }
  bool InAir(){
    return IsInAir;
  }
  void SetInAirFalse(){
    IsInAir = false;
  }
  void SetInAirTrue(){
    IsInAir = true;
  }
  void DropDown(float);
private:
  bool IsJumping = false;
  bool IsInAir = false;
  float pos_x;
  float pos_y;
  int width;
  int height;

  float previousTime;
  float currentTime;
  
  float velocity_y=100.0f;
  float velocity_x =0.0f;
  float gravity = -25.0f;

  float down_velo =100.0f;
};

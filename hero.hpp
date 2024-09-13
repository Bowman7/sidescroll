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
  void Jump();
  
private:
  bool IsJumping = false;
  float pos_x;
  float pos_y;
  int width;
  int height;

  float previousTime;
  float currentTime;
  
  float velocity_y=100.0f;
  float velocity_x =0.0f;
  float gravity = -20.0f;
};

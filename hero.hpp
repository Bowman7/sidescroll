#include"raylib.h"


class Hero{
public:
  Hero();
  ~Hero();

  void Draw();
  void Update();

  void Move(int);
  void SetJumpTrue(){
    IsJumping = true;
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
  float startTime = 0.0f;
  bool LandedYet= false;
};

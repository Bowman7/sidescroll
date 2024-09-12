#include"raylib.h"


class Hero{
public:
  Hero();
  ~Hero();

  void Draw();
  void Update();

  void Move(int);
  void Jump();
private:
  float pos_x;
  float pos_y;
  int width;
  int height;
};

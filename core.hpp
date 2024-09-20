#include"raylib.h"

#include<string>
class Core{
public:
  Core(Camera2D&);
  ~Core();

  void HandleInput(float);
  void Update(float,Camera2D&);
  void Draw(Camera2D&);

  void InitGrid();
  char GetTile(int,int);
  float Clamp(float value, float min,float max);
private:
  //player
  Vector2 fPlayerPos={200.0f,200.0f};

  Vector2 fNewPlayerPos ={0.0f,0.0f};

  float fPlayerVelX=0.0f;
  float fPlayerVelY=0.0f;
  
  std::string grid;
  int gridWidth = 20;
  int gridHeight = 20;

  int nVisibleTileX;
  int nVisibleTileY;
  
  int boxWidth=40;

  //falg
  bool bPlayerOnGround = false;
  
};

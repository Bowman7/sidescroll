#include"raylib.h"

#include<string>
class Core{
public:
  Core();
  ~Core();

  void HandleInput();
  void Update(float);
  void Draw();

  void InitGrid();
  char GetTile(int,int);
private:
  //player
  Vector2 fPlayerPos={0.0f,0.0f};

  Vector2 fNewPlayerPos ={0.0f,0.0f};

  float fPlayerVelX=0.0f;
  float fPlayerVelY=0.0f;
  
  std::string grid;
  int gridWidth = 20;
  int gridHeight = 20;

  int nVisibleTileX;
  int nVisibleTileY;
  int boxWidth=40;
  
};

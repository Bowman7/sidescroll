#include"raylib.h"

#include<string>
#include<fstream>


struct Enemy{
  float posX;
  float posY;
  Color color;
  int nDim;
  bool alive;
};

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
  void SetupEnemyPos();
  void UpdatePlayerPos(float);
  void CoreCollision();
  void UpdateCamera(Camera2D&);
  void UpdateHealth();
  bool IsTimeElapsed(float);
  void UpdateEnemy();
  void GameInit();
private:
  //texture stuff
  Image Ibackground;
  Texture2D Tbackground;
  float lastElapsedTime = GetTime();
  int count =0;
  bool setDir = false;//-ve
  //enemy
  Enemy enemy[8];
  //player
  int health;
  bool OnLand=true;
  int HeightCount =0;
  
  Vector2 fPlayerPos={0.0f,0.0f};

  Vector2 fNewPlayerPos ={0.0f,0.0f};

  float fPlayerVelX=0.0f;
  float fPlayerVelY=0.0f;
  
  std::string grid;
  
  int gridWidth = 20;
  int gridHeight = 20;
  int boxWidth=40;
  //new
  int NewGridWidth = 67;
  int NewGridHeight = 45;
  int NewBoxDim = 16;

  int nVisibleTileX;
  int nVisibleTileY;
  
  

  //falg
  bool bPlayerOnGround = false;
  
};

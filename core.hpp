#include"raylib.h"

#include<string>
#include<fstream>


enum h_Direction{
  east = 0,
  west
};
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
  void UpdateAnimations();
  void GameInit();
  void DrawHealth();
  bool IsGameWon(){
    return gameWon;
  }
  bool IsGameOver(){
    return gameOver;
  }
private:
  Sound jump;
  Sound death;
  //gamewon
  bool gameOver = false;
  bool gameWon =false;
  //heart
  Image heart_image;
  Texture2D heart_texture;
  //for enemy
  h_Direction e_dir;
  Rectangle e_FrameRec;
  int e_CurrentFrame;
  int e_FrameCounter;
  int e_FrameSpeed;
  //for run animation
  bool h_running;
  //for jump animation
  bool h_jump;
  //direction
  h_Direction h_direction;
  //hero tile
  Image hero_image;
  Texture2D hero_texture;
  Rectangle heroFrameRec;
  int heroCurrentFrame;
  int heroFrameCounter ;
  int heroFrameSpeed ;
  //tile stuff
  std::string MainGrid;
  Image tile_image;
  Texture2D tile_texture;
  Rectangle tileFrameRec;
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

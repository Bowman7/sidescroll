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
private:
  std::string grid;
  int gridWidth = 20;
  int gridHeight = 20;

  int boxWidth=40;
};

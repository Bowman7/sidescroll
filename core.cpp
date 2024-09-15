#include"core.hpp"

Core::Core(){
  //gridsetup
  InitGrid();
  nVisibleTileX = 800/gridWidth;
  nVisibleTileY = 800/gridHeight;
}

Core::~Core(){

}


void Core::InitGrid(){
  
  grid +="....................";
  grid +="....................";
  grid +="....#.##########..#.";
  grid +="....#.#...........#.";
  grid +="....#.#........###..";
  grid +="....#.#.......#.....";
  grid +="#####.#......#......";
  grid +="#.....#....##.......";
  grid +="#.####...##.........";
  grid +="#.#.....#...........";
  grid +="#.#....#............";
  grid +="....................";
  grid +="##.##############.##";
  grid +=".#.#.......#......#.";
  grid +=".#.#......#...####..";
  grid +=".#.#....##...#......";
  grid +=".#.#####...##.......";
  grid +=".#........#.........";
  grid +=".#########..........";
  grid +="....................";
 
  printf("size of string: %ld\n",grid.size());
  for(int i=0;i<grid.size();i++){
    if(grid[i] == '\n'){
      printf("\n");
    }else{
      printf(" %c ",grid[i]);
    }
  }

  //print grids
  for(int y=0;y<20;y++){
    printf("%d val: %c \n",y,grid[y*20+0]);
  }
}
void Core::HandleInput(){
  //set velocity to 0 if not pressed
  fPlayerVelX = 0.0f;
  fPlayerVelY = 0.0f;
  
  if(IsKeyDown(KEY_D)){
    fPlayerVelX = 100.0f;
  }
  if(IsKeyDown(KEY_A)){
    fPlayerVelX = -100.0f;
  }
  if(IsKeyDown(KEY_W)){
    fPlayerVelY = -100.0f;
  }
  if(IsKeyDown(KEY_S)){
    fPlayerVelY = 100.0f;
  }
}  

void Core::Update(float dt){
  //move player
  fNewPlayerPos.x = fPlayerPos.x+fPlayerVelX*dt*5;
  fNewPlayerPos.y = fPlayerPos.y+fPlayerVelY*dt*5;
  
  //check collision
  if(fPlayerVelX <=0){
     float x= fNewPlayerPos.x/40;
     float y= fPlayerPos.y/40;
     int x_grid = (int)x;
     int y_grid = (int)y;
    if(GetTile(x+0.0f,y+0.0f) != '.'||
       GetTile(x+0.0f,y+0.9f) != '.'
       ){
      float New_x = fNewPlayerPos.x/40;
      int New_grid_x = (int)New_x +1;
      //New_grid_x +=1;
      //float FinalNewPosX = New_grid_x*40;
      fNewPlayerPos.x = New_grid_x * 40;
      fPlayerVelX = 0.0f;
    }
  }
  else if(fPlayerVelX>0){
    float x=fNewPlayerPos.x/40;
    float y = fPlayerPos.y/40;
    int x_grid = (int)x;
    int y_grid = (int)y;
    if(GetTile(x+1.f,y+0.0f) != '.'||
       GetTile(x+1.0f,y+0.9f) !='.'
       )
      {
	printf("right collision\n");
	printf("current xpos: %f\n",fNewPlayerPos.x);
	float New_x = fNewPlayerPos.x/40;
	int New_grid_x = (int)New_x;

	fNewPlayerPos.x = New_grid_x*40;
	fPlayerVelX =0.0f;
      }
  }
  //for y collision
  if(fPlayerVelY <=0){//up
     float x= fNewPlayerPos.x/40;
     float y= fNewPlayerPos.y/40;
     int x_grid = (int)x;
     int y_grid = (int)y;
    if(GetTile(x+0.0f,y) != '.'||
       GetTile(x+0.9f,y) != '.'
       ){
      float New_y = fNewPlayerPos.y/40;
      int New_grid_y = (int)New_y+1 ;
      //New_grid_x +=1;
      //float FinalNewPosX = New_grid_x*40;
      fNewPlayerPos.y = New_grid_y * 40;
      fPlayerVelY = 0.0f;
    }
  }else{
    
  }
   
  //update player pos
  fPlayerPos.x = fNewPlayerPos.x;
  fPlayerPos.y = fNewPlayerPos.y; 
}
//get tile
char Core::GetTile(int x,int y){
  if(x>=0 && x<gridWidth && y>=0 && y <gridHeight){
    return grid[y*gridWidth+x];
  }else{
    return ' ';
  }
  
}
void Core::Draw(){
  //print grids
  for(int y=0;y<gridHeight;y++){
    //printf("%d val: %c \n",y,grid[y*20+0]);
    for(int x=0;x<gridHeight;x++){
      if(grid[y*gridWidth+x]=='.'){
	DrawRectangle(x*boxWidth,y*boxWidth,boxWidth,boxWidth,BLUE);
      }else if(grid[y*gridWidth+x]=='#'){
	DrawRectangle(x*boxWidth,y*boxWidth,boxWidth,boxWidth,RED);
      }
    }
  } 

  //draw player
  DrawRectangle(fPlayerPos.x,fPlayerPos.y,boxWidth,boxWidth,GREEN);
  //draw lines
  for(int i=0;i<20;i++){
    //vert line
    DrawLine(i*boxWidth,0,i*boxWidth,800,BLACK);
    //horz lines
    DrawLine(0,i*boxWidth,800,i*boxWidth,BLACK);
  }

  
}

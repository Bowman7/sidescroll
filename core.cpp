#include"core.hpp"

Core::Core(Camera2D &camera){
  //gridsetup
  InitGrid();
  
  //init camera
  //camera at center
  camera.target = (Vector2){fPlayerPos.x+20.0f,fPlayerPos.y+20.0f};
  camera.offset = (Vector2){1080.0f/2.0f,720.0f/2.0f};
  camera.rotation = 0.0f;
  camera.zoom = 2.0f;
}

Core::~Core(){

}


void Core::InitGrid(){
  /*
  grid +="....................";
  grid +="......#.#...........";
  grid +=".....##.############";
  grid +="######..############";
  grid +="#####...############";
  grid +="#####...############";
  grid +="#####...############";
  grid +="#.......############";
  grid +="#....###############";
  grid +="#...################";
  grid +="#..#################";
  grid +="....................";
  grid +="#...############..##";
  grid +="##.#########.......#";
  grid +="##.########.....####";
  grid +="##.########...######";
  grid +="##.########..#######";
  grid +="##...............###";
  grid +="####################";
  grid +="####################";
  */
  //read file
  std::ifstream file("level_0.txt");
  if(!file){
    printf("could not open file\n");
  }
  //read tille nd
  std::string line;
  while(getline(file,line)){
    grid += line;
  }

  file.close();
 
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
void Core::HandleInput(float dt){
  //set velocity to 0 if not pressed
  //fPlayerVelX = 0.0f;
  //fPlayerVelY = 0.0f;
  if(bPlayerOnGround){
    //printf("on ground\n");
  }else{
    //printf("not on ground\n");
  }
  if(IsKeyDown(KEY_D) && IsKeyDown(KEY_LEFT_SHIFT)){
    fPlayerVelX += (bPlayerOnGround ? 100.0f: 40.0f)*dt*20;
  }else if(IsKeyDown(KEY_D)){
    fPlayerVelX += (bPlayerOnGround ? 50.0f: 40.0f)*dt*20;
  }
  
  if(IsKeyDown(KEY_A) && IsKeyDown(KEY_LEFT_SHIFT)){
    fPlayerVelX += (bPlayerOnGround?-100.0f:-40.0f)*dt*20;
  }else if(IsKeyDown(KEY_A)){
    fPlayerVelX += (bPlayerOnGround?-50.0f:-40.0f)*dt*20;
  }
  /*
  if(IsKeyDown(KEY_W)){
    fPlayerVelY = -100.0f;
  }
  if(IsKeyDown(KEY_S)){
    fPlayerVelY = 100.0f;
  }
  */

  if(IsKeyPressed(KEY_SPACE)){
    if(fPlayerVelY == 0){
      fPlayerVelY = -84.0f;
    }
  }
}  

void Core::Update(float dt,Camera2D& camera){
  //gravity
  fPlayerVelY += 50.0f*dt*5;
  //resistance
  if(bPlayerOnGround){
    fPlayerVelX += -3.0f*fPlayerVelX*dt;
    if(abs(fPlayerVelX)<0.01f){
      fPlayerVelX = 0.0f;
    }
  }
  //move player
  fNewPlayerPos.x = fPlayerPos.x+fPlayerVelX*dt*5;
  fNewPlayerPos.y = fPlayerPos.y+fPlayerVelY*dt*5;

  //clamp
  if(fPlayerVelX >10.0f){
    fPlayerVelX = 10.0f;
  }
  if(fPlayerVelX < -10.0f){
    fPlayerVelX = -10.0f;
  }
  if(fPlayerVelY > 100.0f){
    fPlayerVelY = 100.0f;
  }
  if(fPlayerVelY < -100.0f){
    fPlayerVelY = -100.0f;
  }

  bPlayerOnGround = false;
  
  //check collision
  if(fPlayerVelX <=0){
     float x= fNewPlayerPos.x/NewBoxDim;
     float y= fPlayerPos.y/NewBoxDim;
     int x_grid = (int)x;
     int y_grid = (int)y;
    if(GetTile(x+0.0f,y+0.0f) != '.'||
       GetTile(x+0.0f,y+0.9f) != '.'
       ){
      float New_x = fNewPlayerPos.x/NewBoxDim;
      int New_grid_x = (int)New_x +1;
      //New_grid_x +=1;
      //float FinalNewPosX = New_grid_x*40;
      fNewPlayerPos.x = New_grid_x * NewBoxDim;
      fPlayerVelX = 0.0f;
    }
  }
  else if(fPlayerVelX>0){
    float x=fNewPlayerPos.x/NewBoxDim;
    float y = fPlayerPos.y/NewBoxDim;
    int x_grid = (int)x;
    int y_grid = (int)y;
    if(GetTile(x+1.f,y+0.0f) != '.'||
       GetTile(x+1.0f,y+0.9f) !='.'
       )
      {
	//printf("right collision\n");
	//printf("current xpos: %f\n",fNewPlayerPos.x);
	float New_x = fNewPlayerPos.x/NewBoxDim;
	int New_grid_x = (int)New_x;

	fNewPlayerPos.x = New_grid_x*NewBoxDim;
	fPlayerVelX =0.0f;
      }
  }
  //for y collision
  if(fPlayerVelY <=0){//up
     float x= fNewPlayerPos.x/NewBoxDim;
     float y= fNewPlayerPos.y/NewBoxDim;
     int x_grid = (int)x;
     int y_grid = (int)y;
    if(GetTile(x+0.0f,y) != '.'||
       GetTile(x+0.9f,y) != '.'
       ){
      float New_y = fNewPlayerPos.y/NewBoxDim;
      int New_grid_y = (int)New_y+1 ;
      //New_grid_x +=1;
      //float FinalNewPosX = New_grid_x*40;
      fNewPlayerPos.y = New_grid_y * NewBoxDim;
      fPlayerVelY = 0.0f;
    }
  }else{//down
    float x = fNewPlayerPos.x/NewBoxDim;
    float y = fNewPlayerPos.y/NewBoxDim;
    int x_grid = (int)x;
    int y_grid = (int)y;
    if(GetTile(x+0.0f,y+1) != '.'||
       GetTile(x+0.9f,y+1) != '.'
       )
      {
	float New_y = fNewPlayerPos.y/NewBoxDim;
	int New_grid_y = (int)New_y;

	fNewPlayerPos.y = New_grid_y*NewBoxDim;
	fPlayerVelY =0.0f;
	bPlayerOnGround = true;
      }
  }
   
  //update player pos
  fPlayerPos.x = fNewPlayerPos.x;
  fPlayerPos.y = fNewPlayerPos.y;

  //update camera pos
  float minX = 0.0f;
  float minY = 0.0f;
  float maxX = NewGridWidth*NewBoxDim -(camera.offset.x/camera.zoom);
  float maxY = NewGridHeight*NewBoxDim -(camera.offset.y/camera.zoom);

  printf("max current x: %f \n",maxX);
  printf("max current y: %f \n",maxY);

  camera.target.x = Clamp(fPlayerPos.x+NewBoxDim/2,
			  minX+camera.offset.x/camera.zoom,
			  maxX
			  );
  camera.target.y = Clamp(fPlayerPos.y+NewBoxDim/2,
			  minY + camera.offset.y/camera.zoom,
			  maxY
			  );

  if(fPlayerPos.y > 516.0f){
    camera.target.y = 524.0f;
  }

  printf("camera target x y: %f %f\n",
	 camera.target.x,camera.target.y);

}
//clamp func
float Core::Clamp(float value, float min,float max){
  if(value<min){
    return min;
  }
  if(value >max ){
    return max;
  }
  return value;
} 
//get tile
char Core::GetTile(int x,int y){
  if(x>=0 && x<NewGridWidth && y>=0 && y <NewGridHeight){
    return grid[y*NewGridWidth+x];
  }else{
    return ' ';
  }
  
}
void Core::Draw(Camera2D& camera){
  //print grids
  for(int y=0;y<=NewGridHeight;y++){
    //printf("%d val: %c \n",y,grid[y*20+0]);
    for(int x=0;x<=NewGridWidth;x++){
      if(grid[y*NewGridWidth+x]=='.'){
	DrawRectangle(x*NewBoxDim,y*NewBoxDim,
		      NewBoxDim,NewBoxDim,BLUE);
      }else if(grid[y*NewGridWidth+x]=='#'){
	DrawRectangle(x*NewBoxDim,y*NewBoxDim,
		      NewBoxDim,NewBoxDim,RED);
      }
    }
  } 

  //draw player
  DrawRectangle(fPlayerPos.x,fPlayerPos.y,NewBoxDim,NewBoxDim,GREEN);
  //draw lines
  
  for(int i=0;i<67;i++){
    //vert line
    DrawLine(i*16,0,i*16,720,BLACK);
  }
  for(int j=0;j<45;j++){
     //horz lines
    DrawLine(0,j*16,1080,j*16,BLACK);
  }
  
  //draw offsetline x
  DrawLine(0,(int)camera.offset.y+camera.target.y,
	   (int)camera.offset.x+camera.target.x,
	   (int)camera.offset.y+camera.target.y,BLACK);
  DrawLine((int)camera.offset.x+camera.target.x,0,
	   (int)camera.offset.x+camera.target.x,
	   (int)camera.offset.y+camera.target.y,BLACK);

  
}

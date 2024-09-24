#include"core.hpp"

Core::Core(Camera2D &camera){
  //gridsetup
  InitGrid();

  //init health
  health = 3;
  //init camera
  //camera at center
  camera.target = (Vector2){fPlayerPos.x+20.0f,fPlayerPos.y+20.0f};
  camera.offset = (Vector2){1080.0f/2.0f,720.0f/2.0f};
  camera.rotation = 0.0f;
  camera.zoom = 2.0f;

  //init enemy
  for(int i=0;i<8;i++){
    enemy[i].posX = 0.0f;
    enemy[i].posY = 0.0f;
    enemy[i].color = ORANGE;
    enemy[i].nDim = 16;
    enemy[i].alive = true;
  }
  //setup enemy pos
  SetupEnemyPos();
  //load texture
  Ibackground = LoadImage("assets/background.png");
  Tbackground = LoadTextureFromImage(Ibackground);
  UnloadImage(Ibackground);
  //load tile
  tile_image = LoadImage("assets/groundtile.png");
  tile_texture = LoadTextureFromImage(tile_image);
  UnloadImage(tile_image);
  tileFrameRec = {0.0f,0.0f,(float)tile_texture.width/11,(float)tile_texture.height}; 
  
}

Core::~Core(){

}

//setup enemy por
void Core::SetupEnemyPos(){
  //for enemy1
  enemy[0].posX = 15;
  enemy[0].posY = 42;
  //for enemy 2
  enemy[1].posX = 17;
  enemy[1].posY = 32;
  //for enemy 3
  enemy[2].posX = 20;
  enemy[2].posY = 32;
  //for enemy 4
  enemy[3].posX = 17;
  enemy[3].posY = 10;
  //for enemy 5
  enemy[4].posX = 51;
  enemy[4].posY = 10;
  //for enemy 6
  enemy[5].posX = 48;
  enemy[5].posY = 21;
  //for enemy 7
  enemy[6].posX = 44;
  enemy[6].posY = 41;
  //for enemy 8
  enemy[7].posX = 49;
  enemy[7].posY = 41;
  
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

void Core::UpdatePlayerPos(float dt){
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
}
//core collision check

void Core::CoreCollision(){
  
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
}
//update camera
void Core::UpdateCamera(Camera2D& camera){
   //camera.target = fPlayerPos;
  //printf("camera target x y: %f %f\n",camera.target.x,camera.target.y);
  
  //update camera pos
  float minX = 0.0f;
  float minY = 0.0f;
  float maxX = NewGridWidth*NewBoxDim -(camera.offset.x/camera.zoom);
  float maxY = NewGridHeight*NewBoxDim -(camera.offset.y/camera.zoom);

  //printf("max current x: %f \n",maxX);
  //printf("max current y: %f \n",maxY);

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

  //printf("camera target x y: %f %f\n",camera.target.x,camera.target.y);
}
//update player health
void Core::UpdateHealth(){
  //check for fall damage
  int x = (int)fPlayerPos.x/NewBoxDim;
  int y = (int)fPlayerPos.y/NewBoxDim;
  char tileBelow = GetTile(x,y+1);
  //printf("player on top of tile: %c\n",tileBelow);
  if(tileBelow == '#'){
    int prevHeight =HeightCount;
    if(prevHeight>0){
      //printf("height fallen: %d\n",prevHeight);
    }
    if(prevHeight>70){
      health--;
      printf("Current Health: %d\n",health);
    }
    HeightCount = 0;
  }else if(tileBelow =='.'){
    HeightCount++;
  }
}
//update enemy pos and stuff
void Core::UpdateEnemy(){
  
  for(int i=0;i<8;i++){
    //check collision for each enemy
    if(enemy[i].alive){
      //aabb for x dir
      float e_x = enemy[i].posX*NewBoxDim;
      float e_y = enemy[i].posY*NewBoxDim;
      
      if(fPlayerPos.x+NewBoxDim > e_x &&
	 fPlayerPos.x < e_x+NewBoxDim &&
	 fPlayerPos.y+NewBoxDim >e_y &&
	 fPlayerPos.y < e_y+NewBoxDim
	 ){
	//check for top damage
	if(fPlayerPos.y+NewBoxDim <= e_y+NewBoxDim/2){
	  printf("enemy dead\n");
	  enemy[i].alive = false;
	  fPlayerVelY *= -2;
	}else{
	  fPlayerVelX *= -30;
	  health--;
	  printf("collision\n");
	  printf("Current health: %d\n",health);
	}
      }
    }
  }
  //printf(" x: %d posX :%d \n",x,enemy[0].posX);
  //move enemy
  //1
  if(IsTimeElapsed(0.1f)){
    if(!setDir){
      for(int i=0;i<8;i++){
	enemy[i].posX -=0.25;
      }
      count++;
    }
    else if(setDir){
      for(int i=0;i<8;i++){
	enemy[i].posX +=0.25;
      }
      count++;
    }
    if(count == 20){
      if(!setDir){
	setDir = true;
      }else{
	setDir = false;
      }
      count =0;
    }
  }
}
//initialize game again
void Core::GameInit(){
  //gridsetup
  InitGrid();

  //init health
  health = 3;
  //init camera/*
  //camera at center
  /*
  camera.target = (Vector2){fPlayerPos.x+20.0f,fPlayerPos.y+20.0f};
  camera.offset = (Vector2){1080.0f/2.0f,720.0f/2.0f};
  camera.rotation = 0.0f;
  camera.zoom = 2.0f;
  */
  //init enemy
  for(int i=0;i<8;i++){
    enemy[i].posX = 0.0f;
    enemy[i].posY = 0.0f;
    enemy[i].color = ORANGE;
    enemy[i].nDim = 16;
    enemy[i].alive = true;
  }
  //setup enemy pos
  SetupEnemyPos();

  fPlayerPos={0.0f,0.0f};
  fNewPlayerPos ={0.0f,0.0f};

  fPlayerVelX=0.0f;
  fPlayerVelY=0.0f;
  
}
void Core::Update(float dt,Camera2D& camera){

  //check if helath 0
  if(health < 0){
    GameInit();
  }
  UpdatePlayerPos(dt);

  CoreCollision();

  UpdateCamera(camera);

  //UpdateHealth();
  UpdateEnemy();
  
   	
}
//check if time elapsed
bool Core::IsTimeElapsed(float time){
  float currentTime = GetTime();
  if(currentTime - lastElapsedTime >= time){
    lastElapsedTime = currentTime;
    return true;
  }
  return false;
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
  //draw background
  DrawTexture(Tbackground,0,0,WHITE);
  //print grids
  for(int y=0;y<=NewGridHeight;y++){
    //printf("%d val: %c \n",y,grid[y*20+0]);
    for(int x=0;x<=NewGridWidth;x++){
      if(grid[y*NewGridWidth+x]=='.'){
	//DrawRectangle(x*NewBoxDim,y*NewBoxDim,
	//      NewBoxDim,NewBoxDim,BLUE);
      }else if(grid[y*NewGridWidth+x]=='#'){
	bool rightDot= (x+1<NewGridWidth) && (grid[y*NewGridWidth+x+1] == '.');
	bool topDot = (y-1 >= 0) && (grid[(y-1)*NewGridWidth+x]=='.');

	if(rightDot && topDot){
	  tileFrameRec.x = 1.0f *(float)tile_texture.width / 11;
	}else{
	  tileFrameRec.x = 0.0f *(float)tile_texture.width / 11;
	}
	DrawTextureRec(tile_texture,tileFrameRec,{(float)x*NewBoxDim,(float)y*NewBoxDim},WHITE);
      }
    }
  } 


  //draw enemies
  for(int i=0;i<8;i++){
    if(enemy[i].alive){
      DrawRectangle(enemy[i].posX*enemy[i].nDim,enemy[i].posY*enemy[i].nDim,
		    enemy[i].nDim,enemy[i].nDim,enemy[i].color);
    }
  }
  //draw player
  DrawRectangle(fPlayerPos.x,fPlayerPos.y,NewBoxDim,NewBoxDim,GREEN);
  //draw lines
  
  for(int i=0;i<67;i++){
    //vert line
    //DrawLine(i*16,0,i*16,720,BLACK);
  }
  for(int j=0;j<45;j++){
     //horz lines
    //DrawLine(0,j*16,1080,j*16,BLACK);
  }

  
}

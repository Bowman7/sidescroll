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
  tileFrameRec = {0.0f,0.0f,(float)tile_texture.width/14,(float)tile_texture.height};
  //hero texture stuff
  hero_image = LoadImage("assets/hero.png");
  hero_texture = LoadTextureFromImage(hero_image);
  UnloadImage(hero_image);
  heroFrameRec = {0.0f,0.0f,(float)hero_texture.width/5,(float)hero_texture.height/8};
  heroCurrentFrame = 0;
  heroFrameCounter = 0;
  heroFrameSpeed = 5;
  //for hero jumping
  h_jump = false;
  //for run animation
  h_running = false;

  //for enemy
  e_FrameRec ={0.0f,96.0f,(float)hero_texture.width/5,
    (float)hero_texture.height/8};
  e_CurrentFrame = 0;
  e_FrameCounter = 0;
  e_FrameSpeed = 5;
  //for heart
  heart_image = LoadImage("assets/heart.png");
  heart_texture = LoadTextureFromImage(heart_image);
  UnloadImage(heart_image);
  //load sound
  //InitAudioDevice();
  jump = LoadSound("music/jump.mp3");
  death = LoadSound("music/death.mp3");
  
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
 
  //setup main grid
   for(int y=0;y<NewGridHeight;y++){
    for(int x=0;x<NewGridWidth;x++){
      if(grid[y*NewGridWidth+x]=='.'){
	//do nothing
      }else if(grid[y*NewGridWidth+x]=='#'){
	bool rightDot= (x+1<NewGridWidth) && (grid[y*NewGridWidth+x+1] == '.');
	bool topDot = (y-1 >= 0) && (grid[(y-1)*NewGridWidth+x]=='.');
	bool leftDot = (x-1>=0) && (grid[y*NewGridWidth+x-1] == '.');
	bool bottomDot = (y+1 <NewGridHeight) && (grid[(y+1)*NewGridWidth+x] == '.');
	if(rightDot && topDot && !bottomDot && !leftDot){
	  grid[y*NewGridWidth+x] = '2';
	}else if(topDot && bottomDot && rightDot && !leftDot){
	  grid[y*NewGridWidth+x] = '3';
	}else if(topDot && bottomDot && leftDot && !rightDot){
	  grid[y*NewGridWidth+x] = '4';
	}else if(topDot && bottomDot && leftDot && rightDot){
	  grid[y*NewGridWidth+x] = '5';
	}else if(!topDot && !bottomDot && !leftDot && rightDot){
	  grid[y*NewGridWidth+x] = '6';
	}else if(topDot && !bottomDot && leftDot && !rightDot){
	  grid[y*NewGridWidth+x] = '7';
	}else if(topDot && !bottomDot && !leftDot && !rightDot){
	  grid[y*NewGridWidth+x] = '8';
	}else if(topDot && !bottomDot && leftDot && rightDot){
	  grid[y*NewGridWidth+x] = '9';
	}else if(topDot && bottomDot && !leftDot && !rightDot){
	  grid[y*NewGridWidth+x] = 'A';
	}else if(!topDot && !bottomDot && leftDot && rightDot){
	  grid[y*NewGridWidth+x] = 'B';
	}else if(!topDot && !bottomDot && leftDot && !rightDot){
	  grid[y*NewGridWidth+x] = 'C';
	}else if(!topDot && bottomDot && !leftDot && !rightDot){
	  grid[y*NewGridWidth+x] = 'D';
	}else if(!topDot && bottomDot && leftDot && !rightDot){
	  grid[y*NewGridWidth+x] = 'E';
	}else{
	  //set it to 1
	  grid[y*NewGridWidth+x] = '1';
 	}
	
      }
    }
  } 

  //print grids
  for(int y=0;y<20;y++){
    //printf("%d val: %c \n",y,grid[y*20+0]);
  }
}
void Core::HandleInput(float dt){
  
  if(IsKeyDown(KEY_D) && IsKeyDown(KEY_LEFT_SHIFT)){
    h_direction = east;
    h_running = true;
    fPlayerVelX += (bPlayerOnGround ? 100.0f: 40.0f)*dt*20;
  }else if(IsKeyDown(KEY_D)){
    h_direction = east;
    h_running = true;
    fPlayerVelX += (bPlayerOnGround ? 50.0f: 40.0f)*dt*20;
  }
  
  if(IsKeyDown(KEY_A) && IsKeyDown(KEY_LEFT_SHIFT)){
    h_direction = west;
    h_running = true;
    fPlayerVelX += (bPlayerOnGround?-100.0f:-40.0f)*dt*20;
  }else if(IsKeyDown(KEY_A)){
    h_direction = west;
    h_running = true;
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
    PlaySound(jump);
    h_jump= true;
    h_running = false;
    if(fPlayerVelY == 0){
      fPlayerVelY = -84.0f;
    }
  }
  //check if left or right is not being pressed
  if(IsKeyUp(KEY_D) && IsKeyUp(KEY_A)){
    h_running = false;
  }
  
  //h_running = false;
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
	  // printf("enemy dead\n");
	  PlaySound(death);
	  enemy[i].alive = false;
	  fPlayerVelY *= -2;
	}else{
	  fPlayerVelX *= -30;
	  health--;
	  //printf("collision\n");
	  //printf("Current health: %d\n",health);
	}
      }
    }
  }
  //printf(" x: %d posX :%d \n",x,enemy[0].posX);
  //move enemy
  //1
  if(IsTimeElapsed(0.1f)){
    if(!setDir){
      e_dir = west;
      for(int i=0;i<8;i++){
	enemy[i].posX -=0.25;
      }
      count++;
    }
    else if(setDir){
      e_dir = east;
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

  gameWon = false;
  gameOver = false;
  
}
//update all niamtions
void Core::UpdateAnimations(){
  //update hero frame counter
  heroFrameCounter++;
  if(heroFrameCounter>=(30/heroFrameSpeed)){
    heroFrameCounter = 0;
    heroCurrentFrame++;
    if(heroCurrentFrame>5){
      heroCurrentFrame = 0;
    }
    heroFrameRec.x = (float)heroCurrentFrame*(float)hero_texture.width/5;
    //for jumping
    if(h_jump && h_direction == east){
      heroFrameRec.y = 2.0f*(float)hero_texture.height/8;
    }else if(h_jump && h_direction == west){
      heroFrameRec.y =  3.0f*(float)hero_texture.height/8; 
    }else{
      if(h_running){
	if(h_direction == west){
	  heroFrameRec.y = 4.0f*(float)hero_texture.height/8;
	}else if(h_direction == east){
	  heroFrameRec.y = 5.0f*(float)hero_texture.height/8;
	}
      }else{
	if(h_direction == east){
	  heroFrameRec.y =  1.0f*(float)hero_texture.height/8; 
	}else if(h_direction == west){
	  heroFrameRec.y =  0.0f*(float)hero_texture.height/8; 
	}
      }
    }
    //for enemy animation
    e_FrameCounter++;
    if(e_FrameCounter >=(0.5/e_FrameSpeed)){
      e_FrameCounter = 0;
      e_CurrentFrame++;
      if(e_CurrentFrame>5){
	e_CurrentFrame = 0;
      }
      e_FrameRec.x = (float)e_CurrentFrame*(float)hero_texture.width/5;
      if(e_dir == east){
	e_FrameRec.y = 7.0f*(float)hero_texture.height/8;
      }else if(e_dir == west){
	e_FrameRec.y = 6.0f*(float)hero_texture.height/8;
      }
    }
  }
  
  //update if jumping or not
  float x = fPlayerPos.x/NewBoxDim;
  float y = fPlayerPos.y/NewBoxDim;
  int x_grid = (int)x;
  int y_grid = (int)y;
  char down = GetTile(x_grid,y_grid+1);
  //printf("down is: %c\n",down);
  if(down != '.'){
    h_jump = false;
    //printf("Not jumping\n");
  }else{
    h_jump = true;
    //printf("Jumping\n");
  }
}
void Core::Update(float dt,Camera2D& camera){

  //check if helath 0
  if(health <= 0){
    gameOver = true;
    //GameInit();
  }
  UpdatePlayerPos(dt);

  CoreCollision();

  UpdateCamera(camera);

  //UpdateHealth();
  UpdateEnemy();

  UpdateAnimations();

  //check for game won
  float x = fPlayerPos.x/NewBoxDim;
  float y = fPlayerPos.y/NewBoxDim;
  int x_g = (int)x;
  int y_g = (int)y;
  //printf("x: %d y: %d\n",x_g,y_g);
  if(x_g == 62 && y_g == 2){
    //printf("GAME WONNN!\n");
    gameWon = true;
    
  }
  
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
  for(int y=0;y<NewGridHeight;y++){
    //printf("%d val: %c \n",y,grid[y*20+0]);
    for(int x=0;x<NewGridWidth;x++){
      if(grid[y*NewGridWidth+x]=='1'){
	tileFrameRec.x = 0.0f *(float)tile_texture.width / 14;
	DrawTextureRec(tile_texture,tileFrameRec,{(float)x*NewBoxDim,(float)y*NewBoxDim},WHITE);
      }else if(grid[y*NewGridWidth+x] =='2'){
	tileFrameRec.x = 1.0f *(float)tile_texture.width / 14;
	DrawTextureRec(tile_texture,tileFrameRec,{(float)x*NewBoxDim,(float)y*NewBoxDim},WHITE);
      }else if(grid[y*NewGridWidth+x] =='3'){
	tileFrameRec.x = 2.0f *(float)tile_texture.width / 14;
	DrawTextureRec(tile_texture,tileFrameRec,{(float)x*NewBoxDim,(float)y*NewBoxDim},WHITE);
      }else if(grid[y*NewGridWidth+x] =='4'){
	tileFrameRec.x = 3.0f *(float)tile_texture.width / 14;
	DrawTextureRec(tile_texture,tileFrameRec,{(float)x*NewBoxDim,(float)y*NewBoxDim},WHITE);
      }else if(grid[y*NewGridWidth+x] =='5'){
	tileFrameRec.x = 4.0f *(float)tile_texture.width / 14;
	DrawTextureRec(tile_texture,tileFrameRec,{(float)x*NewBoxDim,(float)y*NewBoxDim},WHITE);
      }else if(grid[y*NewGridWidth+x] =='6'){
	tileFrameRec.x = 5.0f *(float)tile_texture.width / 14;
	DrawTextureRec(tile_texture,tileFrameRec,{(float)x*NewBoxDim,(float)y*NewBoxDim},WHITE);
      }else if(grid[y*NewGridWidth+x] =='7'){
	tileFrameRec.x = 6.0f *(float)tile_texture.width / 14;
	DrawTextureRec(tile_texture,tileFrameRec,{(float)x*NewBoxDim,(float)y*NewBoxDim},WHITE);
      }else if(grid[y*NewGridWidth+x] =='8'){
	tileFrameRec.x = 7.0f *(float)tile_texture.width / 14;
	DrawTextureRec(tile_texture,tileFrameRec,{(float)x*NewBoxDim,(float)y*NewBoxDim},WHITE);
      }else if(grid[y*NewGridWidth+x] =='9'){
	tileFrameRec.x = 8.0f *(float)tile_texture.width / 14;
	DrawTextureRec(tile_texture,tileFrameRec,{(float)x*NewBoxDim,(float)y*NewBoxDim},WHITE);
      }else if(grid[y*NewGridWidth+x] =='A'){
	tileFrameRec.x = 9.0f *(float)tile_texture.width / 14;
	DrawTextureRec(tile_texture,tileFrameRec,{(float)x*NewBoxDim,(float)y*NewBoxDim},WHITE);
      }else if(grid[y*NewGridWidth+x] =='B'){
	tileFrameRec.x = 10.0f *(float)tile_texture.width / 14;
	DrawTextureRec(tile_texture,tileFrameRec,{(float)x*NewBoxDim,(float)y*NewBoxDim},WHITE);
      }else if(grid[y*NewGridWidth+x] =='C'){
	tileFrameRec.x = 11.0f *(float)tile_texture.width / 14;
	DrawTextureRec(tile_texture,tileFrameRec,{(float)x*NewBoxDim,(float)y*NewBoxDim},WHITE);
      }else if(grid[y*NewGridWidth+x] =='D'){
	tileFrameRec.x = 12.0f *(float)tile_texture.width / 14;
	DrawTextureRec(tile_texture,tileFrameRec,{(float)x*NewBoxDim,(float)y*NewBoxDim},WHITE);
      }else if(grid[y*NewGridWidth+x] =='E'){
	tileFrameRec.x = 13.0f *(float)tile_texture.width / 14;
	DrawTextureRec(tile_texture,tileFrameRec,{(float)x*NewBoxDim,(float)y*NewBoxDim},WHITE);
      } 
    }
  }


  //draw enemies
  for(int i=0;i<8;i++){
    if(enemy[i].alive){
      //DrawRectangle(enemy[i].posX*enemy[i].nDim,enemy[i].posY*enemy[i].nDim,
      //enemy[i].nDim,enemy[i].nDim,enemy[i].color);
      DrawTextureRec(hero_texture,e_FrameRec,{
	  (float)enemy[i].posX*enemy[i].nDim,
	  (float)enemy[i].posY*enemy[i].nDim},WHITE);
    }
  }
  //draw player
  //DrawRectangle(fPlayerPos.x,fPlayerPos.y,NewBoxDim,NewBoxDim,GREEN);
  DrawTextureRec(hero_texture,heroFrameRec,fPlayerPos,WHITE);

 
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

void Core::DrawHealth(){
   //draw heart
  for(int i=0;i<health;i++){
    int x = i*10;
    DrawTexture(heart_texture,i*16+x+16,688,WHITE);
  }
  
}

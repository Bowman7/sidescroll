#include"core.hpp"

Core::Core(){
  //gridsetup
  InitGrid();
}

Core::~Core(){

}


void Core::InitGrid(){
  grid +="....................";
  grid +="....................";
  grid +="....................";
  grid +="....................";
  grid +="....................";
  grid +="....................";
  grid +="....................";
  grid +="....................";
  grid +="....................";
  grid +="....................";
  grid +="....................";
  grid +="....................";
  grid +="....................";
  grid +="....................";
  grid +="....................";
  grid +="....................";
  grid +="....................";
  grid +="....................";
  grid +="....................";
  grid +="....................";


  printf("size of string: %ld\n",grid.size());
  for(int i=0;i<grid.size();i++){
    if(i%10==0){
      printf("\n");
    }
    printf(" %c ",grid[i]);
  }
  
}
void Core::HandleInput(){

}

void Core::Update(float dt){

}

void Core::Draw(){
  //draw lines
  for(int i=0;i<20;i++){
    //vert line
    DrawLine(i*width,0,i*width,800,BLACK);
    //horz lines
    DrawLine(0,i*width,800,i*width,BLACK);
  }

  //draw grids
  for(int i=0;i<grid.size()/2;i++){
    for(int j=0;j<grid.size()/2;j++){
      if(grid[j*width+i]=='.'){
	DrawRectangle(i*width,j*width,width,width,RED);
      }
    }
  }
}

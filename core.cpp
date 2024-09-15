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

}

void Core::Update(float dt){

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
  
  //draw lines
  for(int i=0;i<20;i++){
    //vert line
    DrawLine(i*boxWidth,0,i*boxWidth,800,BLACK);
    //horz lines
    DrawLine(0,i*boxWidth,800,i*boxWidth,BLACK);
  }

  
}

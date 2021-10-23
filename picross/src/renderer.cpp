#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>
#include "SDL.h" 


#include "renderer.h"
#include "board.h"

Renderer::Renderer(std::size_t screen_width, std::size_t screen_height):_screen_width(screen_width), _screen_height(screen_height), _xCenter(screen_width/2), _yCenter(screen_height/2) {
  SDL_Init(SDL_INIT_VIDEO);

  _window = SDL_CreateWindow(
    "Picross",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    _screen_width,
    _screen_height,
    0
  );

  _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
  SDL_SetRenderDrawColor(_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(_renderer);
  SDL_RenderPresent(_renderer);
}

Renderer::~Renderer(){
  SDL_DestroyWindow(_window);
  SDL_Quit();
}

void Renderer::LoadBoard(Board* board){
  _board = board;
  _tiles.resize(_board->size());

  _blockSize = 150/_board->rows();

  SDL_Rect* curTile;
  //double xOffset = (r-board->rows()/2)*100;

  for(int r=0;r<_board->rows();r++){
    for(int c=0;c<_board->cols();c++){
      curTile=&(_tiles[board->idx(r,c)]);

      curTile->w=_blockSize;
      curTile->h=_blockSize;

      curTile->x=_xCenter+((c-1)*_blockSize)-_blockSize/2;
      curTile->y=_yCenter+((r-1)*_blockSize)-_blockSize/2;
    }
  }
  _boardMaxX = _tiles[board->idx(board->rows()-1,board->cols()-1)].x+_blockSize;
  _boardMaxY = _tiles[board->idx(board->rows()-1,board->cols()-1)].y+_blockSize;
  _boardMinX = _tiles[board->idx(0,0)].x;
  _boardMinY = _tiles[board->idx(0,0)].y;

}

void Renderer::Render(){

  SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(_renderer);

  std::vector<SDL_Surface*> images;
  std::vector<SDL_Texture*> textures;

  //draw board tiles based on state
  for(size_t i=0; i<_board->size();i++){
    drawTile(&_tiles[i], 100, _board->state_[i]);
  }  

  //draw guide for rows
  for(size_t i=0; i<_board->rows();i++){
    drawRowGuide(_board->calcRowGuideNum(i), i, images, textures);
  }


  //draw guide for cols
  for(size_t i=0; i<_board->cols();i++){
    drawColGuide(_board->calcColGuideNum(i), i, images, textures);
  }
  SDL_RenderPresent(_renderer);

  for(size_t i =0; i<images.size(); i++){
    SDL_FreeSurface(images[i]);
  }
  for(size_t i =0; i<textures.size(); i++){
    SDL_DestroyTexture(textures[i]);
  }
}

void Renderer::drawTile(SDL_Rect* tile, double tileSize, Board::State state){
  switch(state){
    case (Board::State::Solve):
      //std::cout<<"State is Solve"<<std::endl;
      SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0x00, 0xFF);
      SDL_RenderFillRect(_renderer, tile);
      break;
    case (Board::State::Blank):
      //std::cout<<"State is Blank"<<std::endl;
      SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0x00, 0xFF);
      SDL_RenderDrawRect(_renderer, tile);
      break;
    case (Board::State::Mark):
      //std::cout<<"State is Mark"<<std::endl;
      SDL_SetRenderDrawColor(_renderer, 0xFF, 0x00, 0x00, 0xFF);
      SDL_RenderFillRect(_renderer, tile);
      break;
  }
}

void Renderer::drawRowGuide(std::vector<int> rowGuide, std::size_t idx, std::vector<SDL_Surface*>& images, std::vector<SDL_Texture*>& textures){
  std::size_t counter = 0;
  
  for(int i=rowGuide.size()-1; i>-1; i--){

    //Pick which number to display
    if(rowGuide[i]<10){//ignores 2 digit numbers which are not implemented
      std::string filePath = "../graphics/";
      std::string fileName = filePath.append(std::to_string(rowGuide[i]));
      SDL_Surface *image = SDL_LoadBMP(fileName.c_str());
      /* Let the user know if the file failed to load */
      if (!image) {
        printf("Failed to load image at %s: %s\n", fileName.c_str(), SDL_GetError());
      }
      SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, image);

      //Set up location for number to display
      SDL_Rect target;
      
      target.x =-counter*10+_xCenter+((-counter-2)*_blockSize)-_blockSize/2;
      target.y =_yCenter+((idx-1)*_blockSize)-_blockSize/2;
      target.w = _blockSize;
      target.h = _blockSize;
  
      SDL_RenderCopy(_renderer, texture, NULL, &target);
      images.push_back(image);
      textures.push_back(texture);
      counter++;
    }
  }
}

void Renderer::drawColGuide(std::vector<int> colGuide, std::size_t idx, std::vector<SDL_Surface*>& images, std::vector<SDL_Texture*>& textures){
  std::size_t counter = 0;
  
  for(int i=colGuide.size()-1; i>-1; i--){

    //Pick which number to display
    if(colGuide[i]<10){//ignores 2 digit numbers which are not implemented
      std::string filePath = "../graphics/";
      std::string fileName = filePath.append(std::to_string(colGuide[i]));
      SDL_Surface *image = SDL_LoadBMP(fileName.c_str());
      /* Let the user know if the file failed to load */
      if (!image) {
        printf("Failed to load image at %s: %s\n", fileName.c_str(), SDL_GetError());
      }
      SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, image);

      //Set up location for number to display
      SDL_Rect target;
      
      target.x = _xCenter+((idx-1)*_blockSize)-_blockSize/2;
      target.y = -counter*10+_yCenter+((-counter-2)*_blockSize)-_blockSize/2;
      target.w = _blockSize;
      target.h = _blockSize;
  
      SDL_RenderCopy(_renderer, texture, NULL, &target);
      images.push_back(image);
      textures.push_back(texture);
      counter++;
    }
  }
}
void Renderer::MousePosToGame(std::size_t x, std::size_t y){
  if((x>_boardMinX) && (x<_boardMaxX) && (y>_boardMinY) && (y<_boardMaxY)){
    //std::cout<<"On board!"<<std::endl;
    int rowSize =(_boardMaxX-_boardMinX)/_board->rows();
    int colSize =(_boardMaxY-_boardMinY)/_board->cols();

    int r = (y-_boardMinY)/colSize;
    int c = (x-_boardMinX)/rowSize;
    

    //std::cout<<"Tile "<<r<<", "<<c<<std::endl;

    _board->makeGuess(r,c);


  }

}


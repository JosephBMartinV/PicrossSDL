#ifndef RENDERER_H
#define RENDERER_H

#include<memory>
#include<vector>

#include "SDL.h" 
#include "board.h"

class Renderer{
    public://Public member functions
        Renderer(std::size_t screen_width, std::size_t screen_height);
        ~Renderer();

        void LoadBoard(Board* board);
        void Render();
        void drawTile(SDL_Rect* tile, double tileSize, Board::State state);
        void drawRowGuide(std::vector<int> rowGuide, std::size_t idx, std::vector<SDL_Surface*>& images, std::vector<SDL_Texture*>& textures);
        void drawColGuide(std::vector<int> colGuide, std::size_t idx, std::vector<SDL_Surface*>& images, std::vector<SDL_Texture*>& textures);
        void MousePosToGame(std::size_t x, std::size_t y);

    private://Private member variables
    SDL_Window* _window;
    SDL_Renderer* _renderer;

    const std::size_t _screen_width;
    const std::size_t _screen_height;
    const std::size_t _xCenter;
    const std::size_t _yCenter;

    Board* _board;
    std::vector<SDL_Rect> _tiles;

    std::size_t _blockSize;
    std::size_t _boardMaxX;
    std::size_t _boardMaxY;
    std::size_t _boardMinX;
    std::size_t _boardMinY;
};

#endif
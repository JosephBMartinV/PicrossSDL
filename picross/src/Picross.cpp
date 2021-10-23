#include <stdlib.h>
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

#include "SDL.h" 

#include "board.h"
#include "renderer.h"

namespace{
    double FRAME_RATE = 60;
}//namespace

int main(int argc, char *argv[]){

int boardSize=3;

if(argc<2){
    std::cout<<"No Size Selected. Defaulting to 3."<<std::endl;
}
else if(argc>2){
    std::cout<<"Too many arguments. Selecting first argurment as input"<<std::endl;
}
else{    
    try{
        boardSize=std::stoi(argv[1]);
    }
    catch (...){
        std::cout<<"Invalid argument: "<<argv[1]<<". Defaulting to 3"<<std::endl;
    }
    if(boardSize>9){
        std::cout<<"Size cannot be larger than 9. Defaulting to 9"<<std::endl;
        boardSize=9;
    }
    else if(boardSize<3){
        std::cout<<"Size cannot be less than 3. Defaulting to 3"<<std::endl;
        boardSize=3;
    }
}

Renderer renderer(600,400);



std::unique_ptr<Board> test = std::make_unique<Board>(boardSize);
int row;
int col;
bool quit = false;
bool solved = false;
bool buttonDown = false;

renderer.LoadBoard(test.get());

SDL_Event event;
test->printState();
while(!test->checkSolution()){
    auto frame_start = std::chrono::high_resolution_clock::now();
    
    SDL_PollEvent(&event);
    switch (event.type)
        {
        case SDL_QUIT:
            std::cout<<"Quit Event"<<std::endl;
            quit = true;
            break;
        case SDL_WINDOWEVENT_CLOSE:
            SDL_Log("Window %d closed", event.window.windowID);
            break;
        case SDL_MOUSEBUTTONDOWN:
            if(!buttonDown){
                //std::cout<<"Mouse Button Down Event at "<<event.button.x<<", "<<event.button.y<<std::endl;
                buttonDown = true;
                renderer.MousePosToGame(event.button.x,event.button.y);
                test->printState();
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if(buttonDown){
                //std::cout<<"Mouse Button Up Event at "<<event.button.x<<", "<<event.button.y<<std::endl;
                buttonDown = false;
            }
            break;
        }
        
        
    if(quit){
        break;
    }
    renderer.Render();

    std::this_thread::sleep_until(frame_start+std::chrono::duration<double>(1/FRAME_RATE));
}


}
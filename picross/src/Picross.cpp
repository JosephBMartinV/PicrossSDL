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
//Parse arguments to set up boardSize
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
//Initialize Window
Renderer renderer(600,400);
/* Main game loop. Loads a board based on user input and then polls user input while displaying
   the board. Loop waits to maintain 60fps. Loop ends when user quits or board is solved. 
*/
std::unique_ptr<Board> test = std::make_unique<Board>(boardSize);
int row;
int col;
bool quit = false;
bool solved = false;
bool buttonDown = false;
//Preloads renderer values so they don't have to be set every loop.
renderer.LoadBoard(test.get());

SDL_Event event;
test->printState();
while(!test->checkSolution()){
    auto frame_start = std::chrono::high_resolution_clock::now();
    //check for user input
    SDL_PollEvent(&event);
    switch (event.type)
        {
        case SDL_QUIT:// "Ctrl+C"
            std::cout<<"Quit Event"<<std::endl;
            quit = true;
            break;
        case SDL_WINDOWEVENT_CLOSE://Clciking the `x` on the window. Automatically calls SDL_QUIT event
            SDL_Log("Window %d closed", event.window.windowID);
            break;
        case SDL_MOUSEBUTTONDOWN://Any mouse button press has the same effect
            if(!buttonDown){
                //Wait until mouse goes back up before triggering another event
                buttonDown = true;
                renderer.MousePosToGame(event.button.x,event.button.y);
                test->printState();
            }
            break;
        case SDL_MOUSEBUTTONUP://Any mouse button raise
            if(buttonDown){
                //Allow button to be pressed again
                buttonDown = false;
            }
            break;
        }
        
    //break loop if quit is detected    
    if(quit){
        break;
    }
    renderer.Render();//render current state
    
    //Wait for 60fps timer to end
    std::this_thread::sleep_until(frame_start+std::chrono::duration<double>(1/FRAME_RATE));
}


}
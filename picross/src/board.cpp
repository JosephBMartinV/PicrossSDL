#include <cmath>
#include <vector>
#include <random>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <string>

#include "board.h"

//constructor for square board
Board::Board(int s){
    rows_=abs(s);
    cols_=abs(s);

    setBoard();
}

//constructor for rect board
Board::Board(int r, int c){
    rows_=abs(r);
    cols_=abs(c);

    setBoard();
}

int Board::rows(){
    return rows_;
}

int Board::cols(){
    return cols_;
}

int Board::size(){
    return rows_*cols_;
}

int Board::idx(int r, int c){
    return r*rows()+c;
}

//initialize new board
void Board::setBoard(){
    //set boards to correct size
    state_.resize(size());
    solution_.resize(size());
    rowGuides.resize(rows());
    colGuides.resize(cols());
    guideSize_=rows()+1;

    //initialize board state to all Blank (why does fill not work?)
    for(size_t i=0;i<size();i++){
        state_[i]=Blank;
    }
    
    //generate random board (wrap later for different solution generators)
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);

    std::uniform_int_distribution<int> distribution(0,1);
    
    for(size_t i=0; i<size();i++){
        solution_[i]=distribution(generator);
    }
    std::cout<<std::endl;

    for(size_t i=0; i<rows();i++){
        rowGuides[i]=calcRowGuideString(i);
    }

    for(size_t i=0; i<cols();i++){
        colGuides[i]=calcColGuideString(i);
    }

}

void Board::printTop(){
    std::string blankFill;
    blankFill.resize(guideSize_,' ');

    for(size_t j=0;j<guideSize_;j++){
        std::cout<<blankFill;
        for(size_t i=0;i<cols();i++){
            std::cout<<colGuides[i][j];
            std::cout<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}

void Board::printSolution(){
    printTop();
    for(size_t i=0;i<rows();i++){
            std::cout<<rowGuides[i];
        for(size_t j=0;j<cols();j++){
            if(solution_[idx(i,j)]){
            std::cout<<"□ ";
            }
            else{
                std::cout<<"x ";
            }
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}

void Board::printState(){
    printTop();
    for(size_t i=0;i<rows();i++){
        std::cout<<rowGuides[i];
        for(size_t j=0;j<cols();j++){
            switch(state_[idx(i,j)]){
                case Solve : std::cout<<"□ "; break;
                case Blank : std::cout<<"■ "; break;
                case Mark  : std::cout<<"x ";
            }
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}

void Board::makeGuess(int r, int c){
    int id = idx(r,c);
    if(solution_[id]){
        state_[id] = Solve;
    }
    else{
        state_[id] = Mark;
    }
}

bool Board::checkSolution(){
    for(size_t i=0; i<size(); i++){
        if(solution_[i]){
            if(!(state_[i]==Solve))
            return false;
        }
    }
    return true;
}

std::string Board::calcRowGuideString(int r){
    int counter=0;
    int id=0;
    std::string guide;
    
    for(size_t i=0; i<cols(); i++){
        id=idx(r,i);
        if(solution_[id]){
            counter++;
        }
        else{
            if(counter>0){
                guide+=(std::to_string(counter));
                guide+=" ";
                counter=0;
            }
        }
    }
    if(counter>0){
            guide+=(std::to_string(counter));
            guide+=" ";
            counter=0;
    }
    guide.resize(guideSize_,' ');
    return guide;
}

std::vector<int> Board::calcRowGuideNum(int r){
    int counter=0;
    int id=0;
    std::vector<int> guide;
    
    for(size_t i=0; i<cols(); i++){
        id=idx(r,i);
        if(solution_[id]){
            counter++;
        }
        else{
            if(counter>0){
                guide.push_back(counter);
                counter=0;
            }
        }
    }
    if(counter>0){
            guide.push_back(counter);
            counter=0;
    }
    if(guide.empty()){
        guide.push_back(0);
    }

    return guide;
}

std::string Board::calcColGuideString(int c){
    int counter=0;
    int id=0;
    std::string guide;
    
    for(size_t i=0; i<rows(); i++){
        id=idx(i,c);
        if(solution_[id]){
            counter++;
        }
        else{
            if(counter>0){
                guide+=(std::to_string(counter));
                guide+=" ";
                counter=0;
            }
        }
    }
    if(counter>0){
            guide+=(std::to_string(counter));
            guide+=" ";
            counter=0;
    }
    guide.resize(guideSize_,' ');
    return guide;
}

std::vector<int> Board::calcColGuideNum(int c){
    int counter=0;
    int id=0;
    std::vector<int> guide;
    
    for(size_t i=0; i<rows(); i++){
        id=idx(i,c);
        if(solution_[id]){
            counter++;
        }
        else{
            if(counter>0){
                guide.push_back(counter);
                counter=0;
            }
        }
    }
    if(counter>0){
            guide.push_back(counter);
            counter=0;
    }
    
    if(guide.empty()){
        guide.push_back(0);
    }
    return guide;
}
#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>

class Board{
    public:
        Board(int s);
        Board(int r, int c);
        
        enum State {Solve=0, Blank, Mark};
        
        int rows();
        int cols();
        int size();

        int idx(int r, int c);

        void setBoard();
        void printSolution();
        void printState();
        
        std::string calcRowGuideString(int r);
        std::vector<int> calcRowGuideNum(int r);
        std::string calcColGuideString(int c);
        std::vector<int> calcColGuideNum(int r);

        void makeGuess(int r, int c);
        bool checkSolution();

        std::vector<std::string> rowGuides;
        std::vector<std::string> colGuides;

        std::vector<State> state_;

        
    private:
        
        int rows_;
        int cols_;
        int guideSize_{7};
        std::vector<bool> solution_;
        

        //helper function to print top of board
        void printTop();
        

};

#endif
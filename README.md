# PicrossSDL
This project is an implementation of the game Picross using SDL. Originally a Udacity C++ Course Capstone Project, this README defines the criteria outlined by the rubric.

## Build Instructions

This project follows the conventional build proceedures of the Udacity C++ course. They are as follows:

1. In the `picross` directory, run `mkdir build`
2. Run `cd build`
3. Run `cmake ..`
4. Run `make`

This should produce an executable `Picross` which you can execute from the build directory. `Picross` takes one argument: an integer between 3 and 9 inclusive that defines the size of the board. If you select a size outside of this range, the board will initialize with the closest acceptable size. If you supply an incorrect argument (or no argument) the board will default to a size of 3. Some examples are provided below, all from within the `build` directory.

`./Picross 5`: Initializes a game with a board size of 5.

`./Picross`: Initializes a game withe a default board size of 3.

## Libraries

This project only incorperates the `SDL2` library suggested by Udacity. Installation instructions can be found [here](https://wiki.libsdl.org/Installation).

## Project Description

This project is a game programming project built from the ground up. The game selected for this project is Picross, a simple puzzle game also known as Paint By Numbers. The object of the game is to reveal the correct tiles by using numeric guides providing limited information about the number and sequence of correct tiles on the board. Each row and column will have a set of numbers detailing the ordered sequence of tiles to reveal for that line, top-to-bottom, left-to-right. Additional details of how to solve Picross boards can be found [here](https://en.wikipedia.org/wiki/Nonogram#Example).

For this prototype, a board of a user selected size is randomly generated for the player to solve. The grid that appears in the SDL window can be clicked on. If a correct tile is selected, the tile will turn black. If an incorrect tile is selected, the tile will turn red. Additional output will be displayed in the command terminal if that is used to start the program. Note that the generation of a board is completely random, and therefore there is no garuntee that a board will be able to be solved through logic alone. However, there are no actual penalties for incorrect guesses, so you can guess your way to the solution if you want. Alternatively, it is possible (though very rare) to generate a board that is pre-solved (0.5^(boardSize^2)). The game window will close once the board is solved.

Within the `picross` directory, there are two directories. However, only the `src` directory contains C++ code. The `graphics` directory simply contains bitmap images of the integers 0-9 for displaying the numbered guide. The purpose of each file will be explained below.

`Picross.cpp`: Contains the main game loop, as well as initializes the `board` and `renderer` objects. This code is also responsible for sending the user input to the other classes.

`board.cpp/.h`: Contains the information about a picross board, including its size, current state, and solution. It also generates objects that can be parsed by the renderer to be displayed, as well as displays to the terminal for debugging.

`renderer.cpp/.h`: Responsible for displaying the interface through an SDL window.

## Rubric

This section denotes rubric items this project satisfies as well as code references where applicable. Additional requirements may have been met and missed by the developer.

1. The project demonstrates an understanding of C++ functions and control structures.
2. The project reads data from a file and process the data, or the program writes data to a file.
  - Image files are read in both the `drawRowGuideNum()` and `drawColGuideNum()` functions (`renderer.cpp:123`, `renderer.cpp:155`).
3. The project accepts user input and processes the input.
  - Project accepts user input for `boardSize` at `Picross.cpp:28` and accepts live interfacing in `Picross.cpp:61-91`.
4. The project uses Object Oriented Programming techniques.
  - Project implements both the `Board` and `Renderer` classes.
5. Classes use appropriate access specifiers for class members.
  -`board.h` and `renderer.h` both clearly display public and private functions and member variables.
6. The project makes use of references in function declarations.
  - References and addresses are used throughout, though a representative sample can be found in `renderer.h:15-19`.
7. The project uses destructors appropriately.
  - `~Renderer()` is defined in lines `renderer.cpp:29-32`.
8. The project uses smart pointers instead of raw pointers.
  - While mostly using raw pointers to more easily follow SDL2 examples, the main `Board` object is created as a `unique_ptr` in `Picross.cpp:47` to make sure it is properly managed while the `Renderer` class utilizes it.

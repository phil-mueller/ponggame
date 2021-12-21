# CPPND: Capstone Pong Game
This repo contains the capstone project for the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). Based on the starting repo of the [Snake game](https://github.com/udacity/CppND-Capstone-Snake-Game), a clone of the classic arcade game Pong has been developed. The basic structure is taken from this [Tutorial](https://github.com/udacity/CppND-Capstone-Snake-Game) of Austin Morlan. The original code has been enhanced by

* Adding colors
* Restructuring the code into different header and cpp files
* Adding the Game class to hold the game loop
* Ading a FPS counter in the window title
* Adding the PlayerName and GameResult classes for additional features
* Adding reading/writing the last 3 games from a text-file
* Adding an computer enemy for single-player mode

Note: the game has been developed and tested under Linux only. Additionally, detailed installation guides for the required libraries are only given for Linux operating systems. However, all libraries used are also available for Windows and MacOS.

## Program structure
The main file (main.cpp) contains basic settings such as window width and window height. Also, it features the main function that collects user input and spawns a corresponding game object (Game.cpp), which then starts the game loop. Game.cpp uses the SDL2 library to display and control the pong game logic. It thereby uses the individual classes for the ball (Ball.cpp) and paddles (Paddle.cpp) to calculate their movement. 

The help classes PlayerName.cpp and PlayerScore.cpp are used by the game loop to display the current players and their scores on the screen. In Auxiliary.h, some help classes and enums are stored that are required inside the game logic. The Vec2 class (Vec2.cpp) is a general helper class to contain a 2D vector for the physics of the pong game. Finally, the GameResult.cpp class is used to pass the result from a finished game instance back to the main function.

The last three GameResult objects are kept inside a vector in main.cpp and written to the file "lastgames.txt" before the program finishes. If the program detects such an already existing database during start-up, the last three games and their results are printed on the console.

## Rubric points
* README.MD file (all rubric points)
* Compiling and Testing
  * Program compules and runs without errors
  * The compiler shows a warning during build, this is known and not important since it only affects the ASCII art block
* The project demonstrates an understanding of C++ functions and control structures
  * All files: for, if/else, try/catch constructs
  * Game.cpp (lines 14-100) uses functions to detect collisions of ball and walls/paddles
* The project reads data from a file and process the data, or the program writes data to a file
  * main.cpp (lines 19-50 and 123-128) reads and writes from a text-file
* The project accepts user input and processes the input
  * main.cpp (lines 80-97) asks for and processes user input to set the player names, activate the computer enemy and adjust the difficulty
  * The information collected in main.cpp is passed onto game.cpp to influence the game
* The project uses Object Oriented Programming techniques
  * See overall program (all files) structures into classes for game, ball, paddle, score etc.
* Class constructors utilize member initialization lists
  * GameResult.h class constructor uses member intialization list
* Classes encapsulate behavior
  * Ball.cpp (all lines) class includes behavior for bouncing that is called via member function inside the game loop
  * All objects have a "draw" member function to render them to the screen
* Overloaded functions allow the same function to operate on different parameters
  * Operator overloading is used in the Vec2.cpp (lines 15-29) class
* The project makes use of references in function declarations
  * Examples: operator overloading in Vec2.cpp (lines(15-29)) use pass-by-reference, functions CheckWallCollision and CheckPaddleCollision in Game.cpp, functions CollideWithPaddle and CollideWithWall in Ball.cpp
* The project uses destructors appropriately
  * PlayerName.cpp (lines 17-21) and PlayerScore.cpp (18-22)

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* SDL2_TTF
  * On Linux, run `apt-get install libsdl2-ttf-dev`
* SDL2_MIXER
  * On Linux, run `apt-get install libsdl2-mixer-dev`
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./PongGame`.


## Known issues and to-dos
* The audio output does not work inside the Udacity workspace (not fixable currently), therefore all respective audio commands are commented out. If you are running the game locally and which to include audio output, please uncomment these lines
* Further feature ideas to add
  * Add a Start/Exit Menu with GUI
  * Make the artificial computer enemy smarter / less predictable

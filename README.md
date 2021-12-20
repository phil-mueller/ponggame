# CPPND: Capstone Pong Game
This repo contains the capstone projec for the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). Based on the starting repo of the [Snake game](https://github.com/udacity/CppND-Capstone-Snake-Game), a clone of the classic arcade game Pong has been developed. The basic structure is taken from this [Tutorial](https://github.com/udacity/CppND-Capstone-Snake-Game) of Austin Morlan. The original code has been extended with new features and restructured in an object-oriented manner.

Note: the game has been developed and tested under Linux only. Additionally, detailed installation guides for the required libraries are only given for Linux operating systems. However, all libraries used are also available for Windows and MacOS.

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
* The audio output does not work inside the Udacity workspace (not fixable currently), therefore all respective audio commands are commented out. If you are running the
  game locally and which to include audio output, please uncomment these lines
* Further feature ideas to add
  * Add a Start/Exit Menu with GUI
  * Read and save last game results from datafile
  * Make the artificial computer enemy smarter / less predictable

// Game object class for main loop
#ifndef GAME_H
#define GAME_H

#include <Vec2.h>
#include <Auxiliary.h>
#include <Ball.h>
#include <Paddle.h>
#include <PlayerScore.h>
#include <PlayerName.h>
#include <GameResult.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include <SDL2/SDL_ttf.h>
#include <chrono>
#include <ctime>
#include <thread>
#include <sstream>
// #include <SDL2/SDL_audio.h>
// #include <SDL2/SDL_mixer.h>

class Game
{
    public:
        Game(int windowWidthInput, int windowHeightInput, std::string difficultyInput, std::string playerOneNameInput, std::string playerTwoNameInput);
        GameResult Run();
        Contact CheckPaddleCollision(Ball const& ball, Paddle const& paddle);
        Contact CheckWallCollision(Ball const& ball);
    private:
        int windowWidth, windowHeight;
        std::string playerOneName,playerTwoName,difficulty;
};

#endif
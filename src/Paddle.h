// Paddle object class
#ifndef PADDLE_H
#define PADDLE_H

#include <Vec2.h>
#include <SDL2/SDL.h>
#include <string>

class Paddle
{
    public:
        Paddle(int windowWidth, int windowHeight, Vec2 startVelocity, std::string side);
        void Draw(SDL_Renderer* renderer);
        void Update(float dt);
        Vec2 position;
        Vec2 velocity;
        SDL_Rect rect{};
        const int paddleWidth = 10;
        const int paddleHeight = 80;
    private:
        int windowWidthInternal;
        int windowHeightInternal;
};

#endif
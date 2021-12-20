// Ball object class
#ifndef BALL_H
#define BALL_H

#include <Vec2.h>
#include <SDL2/SDL.h>
#include <auxiliary.h>
#include <random>

class Ball
{
    public:
        Ball(int windowWidth, int windowHeight,Vec2 startVelocity);
        void Draw(SDL_Renderer* renderer);
        void Update(float dt);
        void CollideWithPaddle(Contact const& contact,float ballAcceleration);
        void CollideWithWall(Contact const& contact,float ballSpeed);
        Vec2 position;
        Vec2 velocity;
        SDL_Rect rect{};
        const int ballWidth = 10;
        const int ballHeight = 10;
    private:
        int windowWidthInternal;
        int windowHeightInternal;
};

#endif
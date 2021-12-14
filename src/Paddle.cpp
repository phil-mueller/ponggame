#include "Paddle.h"

Paddle::Paddle(int windowWidth, int windowHeight, Vec2 startVelocity, std::string side)
{
    velocity = startVelocity;
    windowWidthInternal = windowWidth;
    windowHeightInternal = windowHeight;

    if(side == "left")
    {
        position = Vec2(50.0f,(windowHeight/2.0f)-(paddleHeight/2.0f));
        rect.x = static_cast<int>(position.x);
        rect.y = static_cast<int>(position.y);
        rect.w = paddleWidth;
        rect.h = paddleHeight;
    }
    else if(side == "right")
    {
        position = Vec2(windowWidth-50.0f,(windowHeight/2.0f)-(paddleHeight/2.0f));
        rect.x = static_cast<int>(position.x);
        rect.y = static_cast<int>(position.y);
        rect.w = paddleWidth;
        rect.h = paddleHeight;
    }
}

void Paddle::Draw(SDL_Renderer* renderer)
{
    rect.y = static_cast<int>(position.y);
    SDL_RenderFillRect(renderer, &rect);
}

void Paddle::Update(float dt)
{
    position += velocity*dt;
    if(position.y < 0)
    {
        position.y = 0;
    }
    else if(position.y>(windowHeightInternal-paddleHeight))
    {
        position.y = windowHeightInternal- paddleHeight;
    }
}
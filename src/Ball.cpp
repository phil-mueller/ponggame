#include "Ball.h"

Ball::Ball(int windowWidth, int windowHeight, Vec2 startVelocity)
{
    position = Vec2((windowWidth/2.0f)-(ballWidth/2.0f),(windowHeight/2.0f)-(ballWidth/2.0f));
    velocity = startVelocity;
    windowWidthInternal = windowWidth;
    windowHeightInternal = windowHeight;
    rect.x = static_cast<int>(position.x);
    rect.y = static_cast<int>(position.y);
    rect.w = ballWidth;
    rect.h = ballHeight;
}

void Ball::Draw(SDL_Renderer* renderer)
{
    rect.x = static_cast<int>(position.x);
    rect.y = static_cast<int>(position.y);
    SDL_RenderFillRect(renderer, &rect);
}

void Ball::Update(float dt)
{
    position += velocity*dt;
}

void Ball::CollideWithPaddle(Contact const& contact, float ballAcceleration)
{
    position.x += contact.penetration;
    velocity.x = -velocity.x*ballAcceleration;
    if (contact.type == CollisionType::Top)
    {
        velocity.y = -0.75*velocity.x;
    }
    else if (contact.type == CollisionType::Bottom)
    {
        velocity.y = 0.75*velocity.x;
    }
}

void Ball::CollideWithWall(Contact const& contact, float ballSpeed, std::string diff)
{
    if ((contact.type == CollisionType::Top)
		    || (contact.type == CollisionType::Bottom))
		{
			position.y += contact.penetration;
			velocity.y = -velocity.y;
            if (diff == "hard")
            {
                std::random_device rd;
                std::default_random_engine eng(rd());
                std::normal_distribution<> distr(0,0.3);
                velocity.y += distr(eng);
            }
		}
		else if (contact.type == CollisionType::Left)
		{
            std::random_device rd;
            std::default_random_engine eng(rd());
            std::uniform_real_distribution<> distr(-0.4,0.4);
			position.x = windowWidthInternal / 2.0f;
			position.y = windowHeightInternal / 2.0f;
			velocity.x = ballSpeed;
			velocity.y = distr(eng) * ballSpeed;
		}
		else if (contact.type == CollisionType::Right)
		{
            std::random_device rd;
            std::default_random_engine eng(rd());
            std::uniform_real_distribution<> distr(-0.4,0.4);
			position.x = windowWidthInternal / 2.0f;
			position.y = windowHeightInternal / 2.0f;
			velocity.x = -ballSpeed;
			velocity.y = distr(eng) * ballSpeed;
		}
}
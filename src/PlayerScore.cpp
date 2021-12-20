#include "PlayerScore.h"

PlayerScore::PlayerScore(Vec2 position, SDL_Renderer* renderer, TTF_Font* font)
{
    surface = TTF_RenderText_Solid(font,"0",{128,128,128,255});
    texture = SDL_CreateTextureFromSurface(renderer,surface);

    int width, height;
    SDL_QueryTexture(texture,nullptr,nullptr,&width,&height);

    rect.x = static_cast<int>(position.x);
    rect.y = static_cast<int>(position.y);
    rect.w = width;
    rect.h = height;
}


PlayerScore::~PlayerScore()
{
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void PlayerScore::Draw(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void PlayerScore::SetScore(SDL_Renderer* renderer, TTF_Font* font, int score)
{
    SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
	surface = TTF_RenderText_Solid(font, std::to_string(score).c_str(), {128, 128, 128, 255});
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	int width, height;
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	rect.w = width;
	rect.h = height;
}
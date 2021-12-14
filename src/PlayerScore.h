// PlayerScore object class
#ifndef PLAYERSCORE_H
#define PLAYERSCORE_H

#include <SDL2/SDL.h>
#include <Vec2.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class PlayerScore
{
    public:
        PlayerScore(Vec2 position, SDL_Renderer* renderer, TTF_Font* font);
        ~PlayerScore();
        void Draw(SDL_Renderer* renderer);
        void SetScore(SDL_Renderer* renderer, TTF_Font* font, int score);
        SDL_Surface* surface{};
        SDL_Texture* texture{};
        SDL_Rect rect{};
};

#endif
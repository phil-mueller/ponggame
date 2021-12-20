// PlayerName object class
#ifndef PLAYERNAME_H
#define PLAYERNAME_H

#include <SDL2/SDL.h>
#include <Vec2.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class PlayerName
{
    public:
        PlayerName(Vec2 position, SDL_Renderer* renderer, TTF_Font* font, std::string name);
        ~PlayerName();
        void Draw(SDL_Renderer* renderer);
    private:
    SDL_Surface* surface{};
    SDL_Texture* texture{};
    SDL_Rect rect{};
};

#endif
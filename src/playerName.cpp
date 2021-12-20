#include <playerName.h>

PlayerName::PlayerName(Vec2 position, SDL_Renderer* renderer, TTF_Font* font, std::string name)
{
    const char *cstr = name.c_str();
    surface = TTF_RenderText_Solid(font,cstr,{128,128,128,255});
    texture = SDL_CreateTextureFromSurface(renderer,surface);

    int width, height;
    SDL_QueryTexture(texture,nullptr,nullptr,&width,&height);
    rect.x = static_cast<int>(position.x);
    rect.y = static_cast<int>(position.y);
    rect.w = width;
    rect.h = height;
}

PlayerName::~PlayerName()
{
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void PlayerName::Draw(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}
#pragma once
#include<SDL.h>
#include"LTexture.h"
class Button {
public:
    Button(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect rect);
    ~Button();

    void Render();
    bool IsClicked();

    SDL_Texture* GetTexture() const;

private:
    SDL_Renderer* m_renderer;
    SDL_Texture* m_texture;
    SDL_Rect m_rect;
};

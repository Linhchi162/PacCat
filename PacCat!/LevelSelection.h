#pragma once
#include <vector>
#include <SDL_ttf.h>
#include "Button.h"
#include "Game.h"

class LevelSelection {
public:


    LevelSelection(SDL_Renderer* renderer);

    ~LevelSelection();
    void HandleEvent(SDL_Event* event);
    void Render();
    int LevelNumber();

    bool LevelButtonIsClick = false;

private:
    static const int NUM_LEVELS = 10;
    static const int BUTTON_SIZE = 90;
    static const int PADDING = 10;
    static const int NUM_BUTTONS_PER_ROW = 5;
    static const int BUTTON_SPACING = ((SCREEN_WIDTH - PADDING * 2) - BUTTON_SIZE * NUM_BUTTONS_PER_ROW) / (NUM_BUTTONS_PER_ROW - 1);


    SDL_Renderer* renderer;
    SDL_Texture* backgroundTexture;
    SDL_Rect backgroundRect;
    SDL_Texture* buttonTexture;
    SDL_Rect buttonRect;
    Button* buttons[NUM_LEVELS];
    TTF_Font* font;

    bool quit = false;
    int levelNumber = 0;
};
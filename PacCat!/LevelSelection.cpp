#include"LevelSelection.h"


LevelSelection::LevelSelection(SDL_Renderer* renderer) : renderer(renderer) {
    // Load resources
    backgroundTexture = IMG_LoadTexture(renderer, "./assets/Background.png");
    backgroundRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    buttonTexture = IMG_LoadTexture(renderer, "./assets/LevelSelectButton.png");
    // Load Font
    font = TTF_OpenFont("./assets/Daydream.ttf", 32);

    buttonRect = { 0, 0, BUTTON_SIZE, BUTTON_SIZE };
    // Create buttons
    for (int i = 0; i < NUM_LEVELS; i++) {
        int row = i / NUM_BUTTONS_PER_ROW;
        int col = i % NUM_BUTTONS_PER_ROW;
        int x = PADDING + col * (BUTTON_SIZE + BUTTON_SPACING);
        int y = PADDING + row * (BUTTON_SIZE + BUTTON_SPACING);
        SDL_Rect rect = { x, y, BUTTON_SIZE, BUTTON_SIZE };
        buttons[i] = new Button(renderer, buttonTexture, rect);
    }
}

LevelSelection::~LevelSelection() {
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(buttonTexture);
    for (int i = 0; i < NUM_LEVELS; i++) {
        delete buttons[i];
    }
}
void LevelSelection::HandleEvent(SDL_Event* event) {


    for (int i = 0; i < NUM_LEVELS; i++) {
        if (buttons[i]->IsClicked()) {
            LevelButtonIsClick = true;
            levelNumber = i + 1;

        }

    }

}

void LevelSelection::Render() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, backgroundTexture, nullptr, &backgroundRect);

    SDL_Color textColor = { 255, 255, 255 };
    for (int i = 0; i < NUM_LEVELS; i++) {
        buttons[i]->Render();
        int row = i / NUM_BUTTONS_PER_ROW;
        int col = i % NUM_BUTTONS_PER_ROW;
        int x = PADDING + col * (BUTTON_SIZE + BUTTON_SPACING) + BUTTON_SIZE / 2;
        int y = PADDING + row * (BUTTON_SIZE + BUTTON_SPACING) + BUTTON_SIZE / 2;
        SDL_Rect textRect = { x, y, BUTTON_SIZE, BUTTON_SIZE };
        string buttonText = to_string(i + 1);
        SDL_Surface* surface = TTF_RenderText_Solid(font, buttonText.c_str(), textColor);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        textRect = { x - surface->w / 2, y - surface->h / 2, surface->w, surface->h };
        SDL_RenderCopy(renderer, texture, nullptr, &textRect);
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);
    }
}

int LevelSelection::LevelNumber()
{
    return levelNumber;
}

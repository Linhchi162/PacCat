#include"LevelSelection.h"


LevelSelection::LevelSelection(SDL_Renderer* renderer) : renderer(renderer) {
    // Load resources
    backgroundTexture = IMG_LoadTexture(renderer, "./assets/Background.png");
    backgroundRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    buttonTexture = IMG_LoadTexture(renderer, "./assets/LevelSelectButton.png");
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
    for (int i = 0; i < NUM_LEVELS; i++) {
        buttons[i]->Render();
    }
}

int LevelSelection::LevelNumber()
{
    return levelNumber;
}

#pragma once
#include<SDL.h>
#include"LText.h"
#include"Button.h"
#include"Settings.h"



using namespace std;

class Menu {
public:
    Menu(SDL_Renderer* renderer, TTF_Font* font) : renderer(renderer), font(font) {
        // Load background texture
        backgroundTexture = LoadTexture("./assets/background.png", renderer);

        // Load button textures
        startTexture = LoadText("Start", { 255, 255, 255 }, font, renderer);
        startButtonRect = { SCREEN_WIDTH / 2 - 128, 200, 256, 64 };
        startButton = new Button(renderer, startTexture, startButtonRect);
        helpTexture = LoadText("Help", { 255, 255, 255 }, font, renderer);
        helpButtonRect = { SCREEN_WIDTH / 2 - 128, 300, 256, 64 };
        helpButton = new Button(renderer, helpTexture, helpButtonRect);

    }

    ~Menu() {
        SDL_DestroyTexture(backgroundTexture);
        SDL_DestroyTexture(startTexture);
        SDL_DestroyTexture(helpTexture);
        delete startButton;
        delete helpButton;
    }

    void Render() {
        // Render background
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

        // Render buttons
        //RenderTexture(renderer, startTexture, SCREEN_WIDTH / 2 - 100, 200, 30, 30);
       // RenderTexture(renderer, helpTexture, SCREEN_WIDTH / 2 - 100, 300, 30, 30);
        startButton->Render();
        helpButton->Render();
    }

    bool HandleEvent(SDL_Event* event) {
        if (event->type == SDL_MOUSEBUTTONDOWN) {
            if (startButton->IsClicked()) {
                return true;  // Start game
            }

            if (helpButton->IsClicked()) {
                // Display help screen
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Help", "This is the help screen", nullptr);
            }
        }

        return false;  // Continue showing menu
    }

private:
    SDL_Renderer* renderer;
    TTF_Font* font;

    SDL_Texture* backgroundTexture;
    SDL_Texture* startTexture;
    SDL_Texture* helpTexture;
    SDL_Rect startButtonRect;
    SDL_Rect helpButtonRect;

    Button* startButton;
    Button* helpButton;
};

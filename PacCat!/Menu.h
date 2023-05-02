#pragma once
#include<SDL.h>
#include"LText.h"
#include"LTexture.h"
#include"Settings.h"



using namespace std;

class Menu {
public:
    Menu(SDL_Renderer* renderer, TTF_Font* font) : renderer(renderer), font(font) {
        // Load background texture
        backgroundTexture = LoadTexture("background.png", renderer);

        // Load button textures
        startTexture = LoadText("Start", { 255, 255, 255 }, font, renderer);
        helpTexture = LoadText("Help", { 255, 255, 255 }, font, renderer);
    }

    ~Menu() {
        SDL_DestroyTexture(backgroundTexture);
        SDL_DestroyTexture(startTexture);
        SDL_DestroyTexture(helpTexture);
    }

    void Render() {
        // Render background
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

        // Render buttons
        RenderTexture(renderer, startTexture, SCREEN_WIDTH / 2 - 100, 200, 30, 30);
        RenderTexture(renderer, helpTexture, SCREEN_WIDTH / 2 - 100, 300, 30, 30);
    }

    bool HandleEvent(SDL_Event* event) {
        if (event->type == SDL_MOUSEBUTTONDOWN) {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);

            // Check if mouse is inside "Help" button
            if (mouseX >= SCREEN_WIDTH / 2 - 100 && mouseX <= SCREEN_WIDTH / 2 + 100 &&
                mouseY >= 300 && mouseY <= 340) {
                // Display help screen
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Help", "This is the help screen", nullptr);
            }

            // Check if mouse is inside "Start" button
            if (mouseX >= SCREEN_WIDTH / 2 - 100 && mouseX <= SCREEN_WIDTH / 2 + 100 &&
                mouseY >= 200 && mouseY <= 240) {
                return true;  // Start game
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
};

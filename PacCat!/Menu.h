#pragma once
#include<SDL.h>
#include"Button.h"
#include"Settings.h"
#include"LText.h"



using namespace std;

class Menu {
public:
    Menu(SDL_Renderer* renderer) : renderer(renderer) {
        // Load background texture
        backgroundTexture = LoadTexture("./assets/background.png", renderer);

        // Load button textures
        startTexture = LoadTexture("./assets/start.png", renderer);
        PressedStartTexture = LoadTexture("./assets/PressedStart.png", renderer);
        startButtonRect = { SCREEN_WIDTH / 2 - 128, 200, 64, 64 };
        startButton = new Button(renderer, startTexture, startButtonRect);



        helpTexture = LoadTexture("./assets/help.png", renderer);
        PressedHelpTexture = LoadTexture("./assets/PressedHelp.png", renderer);
        helpButtonRect = { SCREEN_WIDTH / 2 - 128, 300, 64, 64 };
        helpButton = new Button(renderer, helpTexture, helpButtonRect);

    }

    ~Menu() {
        SDL_DestroyTexture(backgroundTexture);
        SDL_DestroyTexture(startTexture);
        SDL_DestroyTexture(PressedStartTexture);
        SDL_DestroyTexture(helpTexture);
        SDL_DestroyTexture(PressedHelpTexture);
        delete startButton;
        delete helpButton;
    }

    void Render() {
        // Render background
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

        if (startButton->IsClicked()) {
            startButton->SetTexture(PressedStartTexture);
          
        }
        else {
            startButton->SetTexture(startTexture);
           

        if (helpButton->IsClicked()) {
            helpButton->SetTexture(PressedHelpTexture);
           
        }
        else {
            helpButton->SetTexture(helpTexture);
           
        }

        startButton->Render();
        helpButton->Render();
        }
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

    SDL_Texture* backgroundTexture;

    SDL_Texture* startTexture;
    SDL_Texture* PressedStartTexture;
   
    SDL_Texture* helpTexture;
    SDL_Texture* PressedHelpTexture;
    
    SDL_Rect startButtonRect;
    SDL_Rect helpButtonRect;

    Button* startButton;
    Button* helpButton;
};

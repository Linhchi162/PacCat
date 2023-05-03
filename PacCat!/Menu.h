#pragma once
#include<SDL.h>
#include"Button.h"
#include"Settings.h"



using namespace std;

class Menu {
public:
    Menu(SDL_Renderer* renderer) : renderer(renderer) {
        // Load background texture
        backgroundTexture = LoadTexture("./assets/background.png", renderer);
        Logo = LoadTexture("./assets/Logo.png", renderer);

        // Load button textures
        startTexture = LoadTexture("./assets/play.png", renderer);
        PressedStartTexture = LoadTexture("./assets/PressedPlay.png", renderer);
        startButtonRect = { SCREEN_WIDTH / 2 - 27, SCREEN_HEIGHT/ 2, 64, 64 };
        startButton = new Button(renderer, startTexture, startButtonRect);



        helpTexture = LoadTexture("./assets/help.png", renderer);
        PressedHelpTexture = LoadTexture("./assets/PressedHelp.png", renderer);
        helpButtonRect = { SCREEN_WIDTH / 2 - 27, SCREEN_HEIGHT / 2 + 100 , 64, 64 };
        helpButton = new Button(renderer, helpTexture, helpButtonRect);

    }

    ~Menu() {
        SDL_DestroyTexture(backgroundTexture);
        SDL_DestroyTexture(startTexture);
        SDL_DestroyTexture(PressedStartTexture);
        SDL_DestroyTexture(helpTexture);
        SDL_DestroyTexture(PressedHelpTexture);
        SDL_DestroyTexture(Logo);
        delete startButton;
        delete helpButton;
    }
    void SetStartPressed(bool value) {
        isStartPressed = value;
        if (value) {
            startButton->SetTexture(PressedStartTexture);
        }
        else {
            startButton->SetTexture(startTexture);
        }
    }
    void SetHelpPressed(bool value) {
        isHelpPressed = value;
        if (value) {
            helpButton->SetTexture(PressedHelpTexture);
        }
        else {
            helpButton->SetTexture(helpTexture);
        }
    }

    void Render() {
        // Render background
        SDL_RenderCopy(renderer, backgroundTexture,&rbg, NULL);
        SDL_RenderCopy(renderer, Logo, NULL, &LogoRect);

        if (startButton->IsClicked()) {
            SetStartPressed(true);
        }
        if (helpButton->IsClicked()) {

            SetHelpPressed(true);
        }

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


    bool IsStartPressed()
    {
        return isStartPressed;
    }

    bool IsHelpPressed()
    {
        return isHelpPressed;
    }

private:
    SDL_Renderer* renderer;

    SDL_Texture* backgroundTexture;
    SDL_Texture* Logo;

    SDL_Texture* startTexture;
    SDL_Texture* PressedStartTexture;
   
    SDL_Texture* helpTexture;
    SDL_Texture* PressedHelpTexture;
    
    SDL_Rect LogoRect = { SCREEN_WIDTH/4 - 10,SCREEN_HEIGHT/4,370,100 };
    SDL_Rect startButtonRect;
    SDL_Rect helpButtonRect;
    SDL_Rect rbg = { NULL,NULL,640,640 };

    Button* startButton;
    Button* helpButton;

    bool isStartPressed = false;
    bool isHelpPressed = false;
};

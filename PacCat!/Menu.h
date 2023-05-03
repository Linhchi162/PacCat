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
        SDL_DestroyTexture(helpScreenTexture);
        delete startButton;
        delete helpButton;
    }
    void ShowHelpScreen() {

        helpScreenTexture = LoadTexture("./assets/background.png", renderer);
        SDL_Rect destRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

        while (true) {
            SDL_Event event;
            if (SDL_PollEvent(&event)) {
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {
                    break;
                }
                if (event.type == SDL_QUIT) {
                    return;
                }
            }
            SDL_RenderCopy(renderer, helpScreenTexture, NULL, &destRect);
            SDL_RenderPresent(renderer);
        }

 
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
        // Render background and logo
        SDL_RenderCopy(renderer, backgroundTexture,&rbg, NULL);
        SDL_RenderCopy(renderer, Logo, NULL, &LogoRect);

        startButton->Render();
        helpButton->Render();
     
    }

    bool HandleEvent(SDL_Event* event) {
        if (event->type == SDL_MOUSEBUTTONDOWN) {
            if (startButton->IsClicked()) {
                SetStartPressed(true);
                return true;  // Start game
            }

            if (helpButton->IsClicked()) {
                SetHelpPressed(true);
                // Display help screen
               
                SDL_RenderCopy(renderer, helpButton->GetTexture(), NULL, &helpButtonRect);
                SDL_RenderPresent(renderer);
                SDL_Delay(500);
                ShowHelpScreen();
                SetHelpPressed(false);
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
    SDL_Texture* helpScreenTexture;

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

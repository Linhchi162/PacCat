#pragma once

#include"Button.h"
#include"Settings.h"

using namespace std;

class Menu {
public:
    Menu(SDL_Renderer* renderer);

    ~Menu();


    void ShowHelpScreen();

    void SetStartPressed(bool value);
      
    void SetHelpPressed(bool value);

    void Render();

    bool HandleEvent(SDL_Event* event);

    bool IsStartPressed()
    {
        return isStartPressed;
    }

    bool IsHelpPressed()
    {
        return isHelpPressed;
    }

private:
    SDL_Renderer* mrenderer;

    SDL_Texture* backgroundTexture;
    SDL_Texture* Logo;
    SDL_Texture* helpScreenTexture;

    SDL_Texture* startTexture;
    SDL_Texture* PressedStartTexture;
   
    SDL_Texture* helpTexture;
    SDL_Texture* PressedHelpTexture;
    
   
    SDL_Rect startButtonRect;
    SDL_Rect helpButtonRect;
   

    Button* startButton;
    Button* helpButton;


    const char* CLICK_SOUND_PATH = "./assets/Click.wav";
    Mix_Chunk* ClickSound;

    bool isStartPressed = false;
    bool isHelpPressed = false;
};

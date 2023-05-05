#pragma once

#include"Button.h"
#include"Settings.h"
#include"Game.h"

using namespace std;

class Menu {
public:
    Menu(SDL_Renderer* renderer);

    ~Menu();


    void ShowHelpScreen();

    void SetStartPressed(bool value);
      
    void SetHelpPressed(bool value);

    void SetSoundPressed(bool value);

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


    bool IsSoundPressed()
    {
        return isSoundPressed;
    }
    bool isMuted = false;
private:
    SDL_Renderer* mrenderer;

    SDL_Texture* backgroundTexture;
    SDL_Texture* helpScreenTexture;

    SDL_Texture* startButtonTexture;
    SDL_Texture* PressedstartButtonTexture;
   
    SDL_Texture*HelpButtonTexture;
    SDL_Texture* PressedHelpButtonTexture;

    SDL_Texture* SoundButtonTexture;
    SDL_Texture* PressedSoundButtonTexture;
    
   
    SDL_Rect startButtonRect;
    SDL_Rect helpButtonRect;
    SDL_Rect SoundButtonRect;
   

    Button* startButton;
    Button* helpButton;
    Button* soundButton;


   

    bool isStartPressed = false;
    bool isHelpPressed = false;
    bool isSoundPressed = false;
};

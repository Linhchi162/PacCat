#pragma once
#include"Settings.h"
#include"LevelSelection.h"

using namespace std;

class Menu {
public:
    Menu(SDL_Renderer* renderer);

    ~Menu();


    void ShowHelpScreen();

    void SetStartPressed(bool value);

    void SetResumeClicked(bool value);

    void SetHelpPressed(bool value);

    void SetSoundPressed(bool value);

    void SetLevelScreen(bool value);

    void Render();

    void RenderResume();
     
    void SetLevelPressed(bool value);
    

   
    bool HandleEvent(SDL_Event* event);

    bool IsStartPressed()
    {

        return isStartPressed;

    }
    bool IsMuted()
    {
        return isMuted;
    }
    bool IsLevelScreenVisible()
    {
        return isLevelScreenVisible;
    }
    bool IsLevelChoosed()
    {
        return isLevelChoosed;
    }
    bool IsResumeClicked()
    {
        return isResumeClicked;
    }
    int LevelNumber()
    {
        return levelNumber;
    }

   
  
private:
    SDL_Renderer* mrenderer;

    SDL_Texture* backgroundTexture;
    SDL_Texture* helpScreenTexture;

    SDL_Texture* startButtonTexture;
    SDL_Texture* PressedstartButtonTexture;

    SDL_Texture* LevelButtonTexture;
    SDL_Texture* PressedLevelButtonTexture;

    SDL_Texture* ReturnMenuTexture;


    SDL_Texture* ResumeTexture;
    SDL_Texture* PressedResumeTexture;
    

    SDL_Texture* HelpButtonTexture;
    SDL_Texture* PressedHelpButtonTexture;

    SDL_Texture* SoundButtonTexture;
    SDL_Texture* PressedSoundButtonTexture;
    


    SDL_Rect startButtonRect;
    SDL_Rect helpButtonRect;
    SDL_Rect SoundButtonRect;
    SDL_Rect LevelButtonRect;
    SDL_Rect ReturnMenuRect;
    SDL_Rect ResumeRect;
    
    Button* startButton;
    Button* helpButton;
    Button* soundButton;
    Button* levelButton;
    Button* ReturnButton;
    Button* ResumeButton;

    class LevelSelection* levelselection;

    int   levelNumber;


    bool isMuted = false;
    bool isLevelScreenVisible = false;
    bool isLevelChoosed = false;
    bool isResumeClicked = false;
    bool isStartPressed = false;
    bool isHelpPressed = false;
    bool isSoundPressed = false;
};

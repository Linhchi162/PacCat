#include"Menu.h"

Menu::Menu(SDL_Renderer* renderer) {


    mrenderer = renderer;


    // Load Menu Screen texture
    backgroundTexture = LoadTexture("./assets/Background.png", renderer);
    helpScreenTexture = LoadTexture("./assets/helpScreen.png", renderer);


    // Load button textures
      // Start Button:
    startButtonTexture = LoadTexture("./assets/play.png", renderer);
    PressedstartButtonTexture = LoadTexture("./assets/PressedPlay.png", renderer);
    startButtonRect = { 214 , 320 , 64, 64 };
    startButton = new Button(renderer, startButtonTexture, startButtonRect);

    // Help Button:
    HelpButtonTexture = LoadTexture("./assets/help.png", renderer);
    PressedHelpButtonTexture = LoadTexture("./assets/PressedHelp.png", renderer);
    helpButtonRect = { 214 , 420  , 64, 64 };
    helpButton = new Button(renderer, HelpButtonTexture, helpButtonRect);

    // Sound Button:
    SoundButtonTexture = LoadTexture("./assets/Sound.png", renderer);
    PressedSoundButtonTexture = LoadTexture("./assets/PressedSound.png", renderer);
    SoundButtonRect = { 370, 320 , 64, 64 };
    soundButton = new Button(renderer, SoundButtonTexture, SoundButtonRect);

    // Level Button:
    LevelButtonTexture = LoadTexture("./assets/Lv.png", renderer);
    PressedLevelButtonTexture = LoadTexture("./assets/PressedLv.png", renderer);
    LevelButtonRect = { 370 , 420 , 64, 64 };
    levelButton = new Button(renderer, LevelButtonTexture, LevelButtonRect);

    // Return Level Button:
    ReturnMenuTexture = LoadTexture("./assets/Home.png", renderer);
    ReturnMenuRect = { SCREEN_WIDTH / 2 - 27, SCREEN_HEIGHT / 2, 64, 64 };
    ReturnButton = new Button(renderer, ReturnMenuTexture,ReturnMenuRect);

    //Resume Button:
    ResumeTexture = LoadTexture("./assets/Continue.png", renderer);
    ResumeRect = { 500 , 10 , 90, 90 };
    ResumeButton = new Button(renderer, ResumeTexture, ResumeRect);

    levelselection = new LevelSelection(renderer);

}
Menu::~Menu()
{
    SDL_DestroyTexture(backgroundTexture);

    SDL_DestroyTexture(startButtonTexture);
    SDL_DestroyTexture(PressedstartButtonTexture);

    SDL_DestroyTexture(HelpButtonTexture);
    SDL_DestroyTexture(PressedHelpButtonTexture);

    SDL_DestroyTexture(SoundButtonTexture);
    SDL_DestroyTexture(PressedSoundButtonTexture);

    SDL_DestroyTexture(LevelButtonTexture);
    SDL_DestroyTexture(PressedLevelButtonTexture);

    SDL_DestroyTexture(ResumeTexture);


    SDL_DestroyTexture(helpScreenTexture);
    


    delete ResumeButton;
    delete soundButton;
    delete levelButton;
    delete startButton;
    delete helpButton;
    delete levelselection;
}   

void Menu::ShowHelpScreen()
{


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
        SDL_RenderCopy(mrenderer, helpScreenTexture, NULL, NULL);
        SDL_RenderPresent(mrenderer);
    }

}
void Menu::SetStartPressed(bool value)
{
    isStartPressed = value;
    if (value) {
        startButton->SetTexture(PressedstartButtonTexture);
    }
    else {
        startButton->SetTexture(startButtonTexture);
    }
}

void Menu::SetHelpPressed(bool value) {
    isHelpPressed = value;
    if (value) {
        helpButton->SetTexture(PressedHelpButtonTexture);
    }
    else {
        helpButton->SetTexture(HelpButtonTexture);
    }
}

void Menu::SetSoundPressed(bool value) {
    isSoundPressed = value;
    if (value) {
        soundButton->SetTexture(PressedSoundButtonTexture);
    }
    else {
        soundButton->SetTexture(SoundButtonTexture);
    }


}

void Menu::SetResumeClicked(bool value) {
     
    isResumeClicked = value;

}
void Menu::SetLevelPressed(bool value)
{
   
    if (value) {
        levelButton->SetTexture(PressedLevelButtonTexture);
    }
    else {
        levelButton->SetTexture(LevelButtonTexture);
    }
}
void Menu::SetLevelScreen(bool Value)
{
    isLevelScreenVisible = Value;
}
void Menu::RenderResume()
{
    if (!isLevelScreenVisible)
    {
        ResumeButton->Render();
    }
}

void Menu::Render() {
   

    // Render background 
        SDL_RenderCopy(mrenderer, backgroundTexture, NULL, NULL);

    if (!isLevelScreenVisible ) {
        startButton->Render();
        helpButton->Render();
        soundButton->Render();
        levelButton->Render();
    }
   
    if (isLevelScreenVisible)
    {
        SDL_Delay(200);
        SDL_SetRenderDrawColor(mrenderer, 0, 0, 0, 255);
        SDL_RenderClear(mrenderer);
        levelselection->Render();

        ReturnButton->Render();
    }
}
bool Menu::HandleEvent(SDL_Event* event) {
    if (event->type == SDL_MOUSEBUTTONDOWN) {
        if (!isLevelScreenVisible)
        {
            if (startButton->IsClicked()) {
                SetStartPressed(true);

                return true;  // Start game

            }

            if (helpButton->IsClicked()) {

                SetHelpPressed(true);
                // Display help screen

                SDL_RenderCopy(mrenderer, helpButton->GetTexture(), NULL, &helpButtonRect);
                SDL_RenderPresent(mrenderer);
                SetHelpPressed(false);

                SDL_Delay(200);

                ShowHelpScreen();

            }
            if (soundButton->IsClicked()) {

                SetSoundPressed(true);

                // Bouncing 
                SDL_RenderCopy(mrenderer, soundButton->GetTexture(), NULL, &SoundButtonRect);
                SDL_RenderPresent(mrenderer);
                SDL_Delay(200);

                SetSoundPressed(false);
                isMuted = !isMuted;

            }
        }
       
        if (levelButton->IsClicked())
        {
            // Render LevelSelection screen
            isLevelScreenVisible = true;
            SetLevelPressed (true);
            SDL_RenderCopy(mrenderer, levelButton->GetTexture(), NULL, &LevelButtonRect);
            SDL_RenderPresent(mrenderer);
            SDL_Delay(200);
            SetLevelPressed(false);
        }
        if (isLevelScreenVisible) {
            levelselection->HandleEvent(event);
            isLevelChoosed = levelselection->LevelButtonIsClick;
            levelNumber = levelselection->LevelNumber();
            levelselection->LevelButtonIsClick = false;
        }
        if (ReturnButton->IsClicked())
        {
            isLevelScreenVisible = false;
        }
        if (ResumeButton->IsClicked())
        {
            isResumeClicked = true;
        }
    }
    return false;  // Continue showing menu
} 


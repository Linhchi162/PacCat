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
        startButtonRect = { SCREEN_WIDTH / 2 - 27, SCREEN_HEIGHT / 2, 64, 64 };
        startButton = new Button(renderer, startButtonTexture, startButtonRect);
          // Help Button:
       HelpButtonTexture = LoadTexture("./assets/help.png", renderer);
        PressedHelpButtonTexture = LoadTexture("./assets/PressedHelp.png", renderer);
        helpButtonRect = { SCREEN_WIDTH / 2 - 27, SCREEN_HEIGHT / 2 + 100 , 64, 64 };
        helpButton = new Button(renderer,HelpButtonTexture, helpButtonRect);
        // Sound Button:
        SoundButtonTexture = LoadTexture("./assets/Sound.png", renderer);
        PressedSoundButtonTexture = LoadTexture("./assets/PressedSound.png", renderer);
        SoundButtonRect = { SCREEN_WIDTH / 2 - 27, SCREEN_HEIGHT / 2 + 200 , 64, 64 };
        soundButton = new Button(renderer, SoundButtonTexture, SoundButtonRect);

        //Sound
        ClickSound = Mix_LoadWAV(CLICK_SOUND_PATH);
       
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


    SDL_DestroyTexture(helpScreenTexture);

    delete startButton;
    delete helpButton;
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
        SDL_RenderCopy(mrenderer, helpScreenTexture, NULL, &ScreenDst);
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

void Menu::Render() {
    // Render background and logo
 
    SDL_RenderCopy(mrenderer, backgroundTexture, NULL, &ScreenDst);

    startButton->Render();
    helpButton->Render();
    soundButton->Render();


}
bool Menu::HandleEvent(SDL_Event* event) {
    if (event->type == SDL_MOUSEBUTTONDOWN) {
        if (startButton->IsClicked()) {
            Mix_PlayChannel(-1, ClickSound, 0);
            SetStartPressed(true);
            return true;  // Start game

        }

        if (helpButton->IsClicked()) {
            Mix_PlayChannel(-1, ClickSound, 0);
            SetHelpPressed(true);
            // Display help screen

            SDL_RenderCopy(mrenderer, helpButton->GetTexture(), NULL, &helpButtonRect);
            SDL_RenderPresent(mrenderer);
            SDL_Delay(500);
            ShowHelpScreen();
            SetHelpPressed(false);
        }
        if (soundButton->IsClicked()) {
            Mix_PlayChannel(-1, ClickSound, 0);
            SetSoundPressed(true);

            // Bouncing 
            SDL_RenderCopy(mrenderer, soundButton->GetTexture(), NULL, &SoundButtonRect);
            SDL_RenderPresent(mrenderer);
            SDL_Delay(200);


            SetSoundPressed(false);
            isMuted = !isMuted;
           
        }
    }
    return false;  // Continue showing menu
}




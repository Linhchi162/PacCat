#include"Menu.h"

Menu::Menu(SDL_Renderer* renderer) {

    
    mrenderer = renderer;


        // Load Menu Screen texture
        backgroundTexture = LoadTexture("./assets/background.png", renderer);
        Logo = LoadTexture("./assets/Logo.png", renderer);
        helpScreenTexture = LoadTexture("./assets/background.png", renderer);


        // Load button textures
          // Start Button:
        startTexture = LoadTexture("./assets/play.png", renderer);
        PressedStartTexture = LoadTexture("./assets/PressedPlay.png", renderer);
        startButtonRect = { SCREEN_WIDTH / 2 - 27, SCREEN_HEIGHT / 2, 64, 64 };
        startButton = new Button(renderer, startTexture, startButtonRect);
          // Help Button:
        helpTexture = LoadTexture("./assets/help.png", renderer);
        PressedHelpTexture = LoadTexture("./assets/PressedHelp.png", renderer);
        helpButtonRect = { SCREEN_WIDTH / 2 - 27, SCREEN_HEIGHT / 2 + 100 , 64, 64 };
        helpButton = new Button(renderer, helpTexture, helpButtonRect);


        //Sound
        ClickSound = Mix_LoadWAV(CLICK_SOUND_PATH);

    }
Menu::~Menu()
{
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(Logo);

    SDL_DestroyTexture(startTexture);
    SDL_DestroyTexture(PressedStartTexture);

    SDL_DestroyTexture(helpTexture);
    SDL_DestroyTexture(PressedHelpTexture);
 
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
        SDL_RenderCopy(mrenderer, helpScreenTexture, NULL, &HelpScreenDst);
        SDL_RenderPresent(mrenderer);
    }

}
void Menu::SetStartPressed(bool value)
{
    isStartPressed = value;
    if (value) {
        startButton->SetTexture(PressedStartTexture);
    }
    else {
        startButton->SetTexture(startTexture);
    }
}

void Menu::SetHelpPressed(bool value) {
    isHelpPressed = value;
    if (value) {
        helpButton->SetTexture(PressedHelpTexture);
    }
    else {
        helpButton->SetTexture(helpTexture);
    }
}

void Menu::Render() {
    // Render background and logo
    SDL_RenderCopy(mrenderer, backgroundTexture, NULL, NULL);
    SDL_RenderCopy(mrenderer, Logo, NULL, &LogoDst);

    startButton->Render();
    helpButton->Render();

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
    }

    return false;  // Continue showing menu
}




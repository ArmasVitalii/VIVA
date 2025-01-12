#include "GameApp.h"

GameApp::GameApp() : window(nullptr), renderer(nullptr), running(true), 
currentState(SPLASH), splashAlpha(0), splashTimer(0), fadeDuration(4500), fadeIn(true)
{
}

bool GameApp::init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) 
    {
        std::cerr << "SDL could not initialize! SDL Error: "
            << SDL_GetError() << std::endl;
        return false;
    }

    if (!IMG_Init(IMG_INIT_PNG)) 
    {
        std::cerr << "SDL_image could not initialize! SDL_image Error: "
            << IMG_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Eter Game",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);

    if (!window) 
    {
        std::cerr << "Window could not be created! SDL Error: "
            << SDL_GetError() << std::endl;
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        std::cerr << "Renderer could not be created! SDL Error: "
            << SDL_GetError() << std::endl;
        return false;
    }

    // Load textures 
    {
        SDL_Surface* surf = IMG_Load("Intro.png");
        if (!surf)
        {
            std::cerr << "Failed to load splash image: " << IMG_GetError() << std::endl;
            return false;
        }
        splashTexture = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_FreeSurface(surf);
    }
    {
        SDL_Surface* surf = IMG_Load("Menu.png");
        if (!surf) 
        {
            std::cerr << "Failed to load main_menu_bg image: " << IMG_GetError() << std::endl;
            return false;
        }
        mainMenuBg = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_FreeSurface(surf);
    }
    {
        SDL_Surface* surf = IMG_Load("Menu.png");
        if (!surf)
        {
            std::cerr << "Failed to load settings_bg image: " << IMG_GetError() << std::endl;
            return false;
        }
        settingsBg = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_FreeSurface(surf);
    }
    {
        SDL_Surface* surf = IMG_Load("Menu.png");
        if (!surf) 
        {
            std::cerr << "Failed to load game_board_bg image: " << IMG_GetError() << std::endl;
            return false;
        }
        gameBoardBg = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_FreeSurface(surf);
    }

    // Set initial alpha for splash screen
    SDL_SetTextureBlendMode(splashTexture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(splashTexture, splashAlpha);

    initButtons();
    initCards();
    return true;
}

void GameApp::run()
{

}

void GameApp::clean()
{
}

void GameApp::initButtons() //Buttons Initialization (positions can be adjusted)
{
    // Bottom-middle alignment for 3 buttons
    int buttonWidth = 400;
    int buttonHeight = 100;
    int gap = 10;

    // Compute x-coord so that the button is centered horizontally
    int xPos = (SCREEN_WIDTH - buttonWidth) / 2;
    int yPos = SCREEN_HEIGHT - 350; // some offset from bottom

    playButton.rect = { xPos, yPos, buttonWidth, buttonHeight };
    playButton.text = "Play";
    playButton.hovered = false;

    settingsButton.rect = { xPos, yPos + (buttonHeight + gap), buttonWidth, buttonHeight };
    settingsButton.text = "Settings";
    settingsButton.hovered = false;

    quitButton.rect = { xPos, yPos + 2 * (buttonHeight + gap), buttonWidth, buttonHeight };
    quitButton.text = "Quit";
    quitButton.hovered = false;

    // For Settings Menu
    settingsButton1.rect = { 200, 200, buttonWidth, buttonHeight };
    settingsButton1.text = "Option A";
    settingsButton1.hovered = false;

    settingsButton2.rect = { 200, 310, buttonWidth, buttonHeight };
    settingsButton2.text = "Option B";
    settingsButton2.hovered = false;

    settingsButton3.rect = { 200, 420, buttonWidth, buttonHeight };
    settingsButton3.text = "Option C";
    settingsButton3.hovered = false;

    settingsBackButton.rect = { 200, 530, buttonWidth, buttonHeight };
    settingsBackButton.text = "Back";
    settingsBackButton.hovered = false;
}

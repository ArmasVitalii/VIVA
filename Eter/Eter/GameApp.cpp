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



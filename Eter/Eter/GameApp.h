#pragma once

#include <SDL_ttf.h>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <vector>


static const int SCREEN_WIDTH = 1920;
static const int SCREEN_HEIGHT = 1080;
static const int FPS = 60;
static const int FRAME_DELAY = 1000 / FPS; 

struct Button {
    SDL_Rect rect;
    std::string text;
    bool hovered;
};

struct Cardx {
    SDL_Rect rect;     
    bool beingDragged;
    int offsetX, offsetY; 
    bool faceUp;      
    int value;
    SDL_Texture* texture;
};

struct BoardCell {
    int cardOwner; 
    int cardIndex;
};

static const int BOARD_ROWS = 5;
static const int BOARD_COLS = 5;

struct Boardx {
    BoardCell cells[BOARD_ROWS][BOARD_COLS];
    int cellWidth;
    int cellHeight;
    int boardX, boardY;
};

struct Player_UI {
    std::vector<Cardx> hand;
};

enum class GameMode {
    SEVEN_CARDS,
    TEN_CARDS,
    TRAINING
};

enum GameState {
    SPLASH,
    MAIN_MENU,
    SETTINGS,
    PLAY,
    QUIT
};


class GameApp {
public:
    GameApp();
    bool init();
    void run();
    void clean();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    TTF_Font* m_font;
    
    SDL_Texture* splashTexture;
    int splashAlpha;
    Uint32 splashTimer;
    int fadeDuration;
    bool fadeIn;

    SDL_Texture* mainMenuBg;
    SDL_Texture* settingsBg;
    SDL_Texture* gameBoardBg;

    Button playButton, settingsButton, quitButton;
    Button settingsButton1, settingsButton2, settingsButton3, settingsBackButton;

    Boardx gameBoard;

    Player_UI player1;
    Player_UI player2;
    int currentPlayerIndex;   

    GameMode selectedGameMode;

    GameState currentState;
    bool running;

    std::vector<SDL_Texture*>blueCardTextures;
    std::vector<SDL_Texture*>redCardTextures;

    Uint32 getTick();

    void initButtons();
    void initBoard();
    void initCardTextures();
    void initPlayerHands();
    void cleanCardTextures();

    void handleEvents();
    void update(Uint32 deltaTime);
    void render();

    void renderText(SDL_Renderer* renderer, const std::string& text, TTF_Font* font, SDL_Color color, SDL_Rect* buttonRect);

    void updateSplash(Uint32 deltaTime);
    void renderSplash();

    void updateMainMenu();
    void renderMainMenu();

    void updateSettingsMenu();
    void renderSettingsMenu();

    void updateGameBoard(Uint32 deltaTime);
    void renderGameBoard();

    bool isMouseOverButton(int mouseX, int mouseY, const Button& btn);
    void startGame();
    void switchTurns();
    void placeCardOnBoard(Cardx& card, int ownerID, int cardIndex);
};

#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <vector>

// --------------------------------------------------------------------
// CONFIG CONSTANTS
// --------------------------------------------------------------------
static const int SCREEN_WIDTH = 1920;
static const int SCREEN_HEIGHT = 1080;
static const int FPS = 60;
static const int FRAME_DELAY = 1000 / FPS; // ~16ms per frame at 60 FPS

// --------------------------------------------------------------------
// STRUCTS AND CLASSES
// --------------------------------------------------------------------

// A simple structure for a button
struct Button {
    SDL_Rect rect;
    std::string text;
    bool hovered;
};

// A card structure, stored in each player's hand
struct Cardx {
    SDL_Rect rect;     // Card position/size on screen
    bool beingDragged;
    int offsetX, offsetY; // For mouse dragging offsets
    bool faceUp;       // True if visible to the user, false if hidden
};

// Board cell to track which card is placed
struct BoardCell {
    int cardOwner; // 0 or 1, or -1 if empty
    int cardIndex; // index of card in player's hand, or -1 if empty
};

static const int BOARD_ROWS = 5;
static const int BOARD_COLS = 5;

// Board data
struct Boardx {
    BoardCell cells[BOARD_ROWS][BOARD_COLS];
    int cellWidth;
    int cellHeight;
    int boardX, boardY;
};

// Each player has a hand (vector of cards)
struct Player_UI {
    std::vector<Cardx> hand;
};

// Possible game modes for how many cards each player gets
enum class GameMode {
    SEVEN_CARDS,
    TEN_CARDS
};

// States in the game
enum GameState {
    SPLASH,
    MAIN_MENU,
    SETTINGS,
    PLAY,
    QUIT
};

// --------------------------------------------------------------------
// MAIN APPLICATION CLASS
// --------------------------------------------------------------------
class GameApp {
public:
    GameApp();
    bool init();
    void run();
    void clean();

private:
    // SDL window/renderer
    SDL_Window* window;
    SDL_Renderer* renderer;

    // Splash / Fade logic
    SDL_Texture* splashTexture;
    int splashAlpha;
    Uint32 splashTimer;
    int fadeDuration;
    bool fadeIn;

    // Textures for backgrounds
    SDL_Texture* mainMenuBg;
    SDL_Texture* settingsBg;
    SDL_Texture* gameBoardBg;

    // Buttons
    Button playButton, settingsButton, quitButton;
    Button settingsButton1, settingsButton2, settingsButton3, settingsBackButton;

    // Board data
    Boardx gameBoard;

    // Two players
    Player_UI player1;
    Player_UI player2;
    int currentPlayerIndex;   // 0 or 1

    // Selected game mode
    GameMode selectedGameMode;

    // State management
    GameState currentState;
    bool running;

    // ------------- PRIVATE METHODS -------------
    Uint32 getTick();

    // Initialization helpers
    void initButtons();
    void initBoard();

    // Event, update, render loops
    void handleEvents();
    void update(Uint32 deltaTime);
    void render();

    // Splash
    void updateSplash(Uint32 deltaTime);
    void renderSplash();

    // Main menu
    void updateMainMenu();
    void renderMainMenu();

    // Settings
    void updateSettingsMenu();
    void renderSettingsMenu();

    // Game board (PLAY state)
    void updateGameBoard(Uint32 deltaTime);
    void renderGameBoard();

    // Actions
    bool isMouseOverButton(int mouseX, int mouseY, const Button& btn);
    void startGame();
    void switchTurns();
    void placeCardOnBoard(Cardx& card, int ownerID, int cardIndex);
};

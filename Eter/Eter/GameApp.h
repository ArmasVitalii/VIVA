#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <vector>

static const int SCREEN_WIDTH = 1920;
static const int SCREEN_HEIGHT = 1080;
static const int FPS = 60;
static const int FRAME_DELAY = 1000 / FPS;


////////////////////////////////////////////////Board Logic
static const int BOARD_ROWS = 5;
static const int BOARD_COLS = 5;

struct BoardCell {
	int cardOwner;  // 0 or 1 (which player), or -1 if empty
	int cardIndex;  // index of card in the player’s hand, or -1 if empty
};

class Board_UI {
public:
	BoardCell cells[BOARD_ROWS][BOARD_COLS];

	// Could store coordinate system or cell size here
	int cellWidth, cellHeight;
	int boardX, boardY; // top-left corner of the 5×5 grid
};
///////////////////////////////////////////////////////////////////////////////




//Button and Card Structs
struct Button {
	SDL_Rect rect;
	std::string text;
	bool hovered;
};

////////////////////////////////
enum class GameMode {
	SEVEN_CARDS,
	TEN_CARDS
};
//////////////////////////////////////

struct Cardx {
	SDL_Rect rect;			//The position and size on the screen
	bool beingDragged;		//Are we currently dragging this card?
	int offsetX, offsetY;	// Mouse offsets when dragging
	bool faceUp;
};

//////////////////////////////////////////
struct Player_UI {
	std::vector<Cardx> hand;  // The cards this player holds
	// You can also store “name”, “score”, etc.
};
//////////////////////////////////////////


//Game Application Class
class GameApp {
public:
	GameApp();
	bool init();
	void run();
	void clean();
	void switchTurns();

private:
	//////////////////////////////////////////

	Player_UI player1;
	Player_UI player2;
	int currentPlayerIndex;  // 0 = player1’s turn, 1 = player2’s turn

	GameMode selectedGameMode;

	Board_UI gameBoard;

	void initBoard();
	void startGame();
	void placeCardOnBoard(Cardx& card, int ownerID, int cardIndex);
	//////////////////////////////////////////

	//SDL Components
	SDL_Window* window;
	SDL_Renderer* renderer;

	//Textures and Splash
	SDL_Texture* splashTexture;		//current alpha value 0..255
	SDL_Texture* mainMenuBg;		//how long we’ve been in the splash state (ms)
	SDL_Texture* settingsBg;		//total fade in + fade out time in ms
	SDL_Texture* gameBoardBg;		// whether we are in fade in or fade out

	//Splash/Fade Logic
	int splashAlpha;
	Uint32 splashTimer;
	int fadeDuration;
	bool fadeIn;

	//Main Menu and Settings
	Button playButton, settingsButton, quitButton;
	Button settingsButton1, settingsButton2, settingsButton3, settingsBackButton;

	//Game Board
	std::vector<Cardx> cards;	//The 5 movable cards
	SDL_Point boardPos;			// Where to draw the board

	enum GameState {
		SPLASH,
		MAIN_MENU,
		SETTINGS,
		PLAY,
		QUIT
	};
	GameState currentState;
	bool running;

	//Private Helper Functions
	Uint32 getTick();
	void handleEvents();
	void update(Uint32 deltaTime);
	void render();

	void updateSplash(Uint32 deltaTime);
	void renderSplash();

	void renderMainMenu();
	void updateMainMenu(); 

	void renderSettingsMenu();
	void updateSettingsMenu();

	void renderGameBoard();
	void updateGameBoard(Uint32 deltaTime);

	void initButtons();
	void initCards();
	bool isMouseOverButton(int mouseX, int mouseY, const Button& btn);
};
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <vector>

static const int SCREEN_WIDTH = 1920;
static const int SCREEN_HEIGHT = 1080;
static const int FPS = 60;
static const int FRAME_DELAY = 100 / FPS;

//Button and Card Structs
struct Button {
	SDL_Rect rect;
	std::string text;
	bool hovered;
};

struct Card {
	SDL_Rect rect;
	bool beingDragged;
	int offsetX, offsetY;
};

//Game Application Class
class GameApp {
public:
	GameApp();
	bool init();
	void run();
	void clean();

private:
	//SDL Components
	SDL_Window* window;
	SDL_Renderer* renderer;

	//Textures and Splash
	SDL_Texture* splashTexture;
	SDL_Texture* mainMenuBg;
	SDL_Texture* settingsBg;
	SDL_Texture* gameBoardBg;

	//Splash/Fade Logic
	int splashAlpha;
	Uint32 splashTimer;
	int fadeDuration;
	bool fadeIn;

	//Main Menu and Settings
	Button playButton, settingsButton, quitButton;
	Button settingsButton1, settingsButton2, settingsButton3, settingsBackButton;

	//Game Board
	std::vector<Card> cards;
	SDL_Point boardPos;

	enum GameState {
		SPLASH, MAIN_MENU, SETTINGS, PLAY, QUIT
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
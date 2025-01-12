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

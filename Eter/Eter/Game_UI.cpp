#include <SDL.h>
module Game_UI;

Game_UI::Game_UI() {

}

Game_UI::~Game_UI() {

}

void Game_UI::initUI(const char* title, int x_pos, int y_pos, int width, int height, bool fullscreen) {

	int flags = 0;

	if (fullscreen == true)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{

		std::cout << "Subsistems Initialized" << std::endl;
		window = SDL_CreateWindow(title, x_pos, y_pos, width, height, flags);
	}

}

void Game_UI::handleEvents()
{
}

void Game_UI::update()
{
}

void Game_UI::render()
{
}

void Game_UI::clean()
{

}
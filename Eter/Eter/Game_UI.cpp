#include <SDL.h>
module Game_UI;

Game_UI::Game_UI()
{
	this->initUI("Eter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, false);

}

Game_UI::~Game_UI()
{

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
		if (window)
		{
			std::cout << "Window created" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created" << std::endl;
		}

		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

}

void Game_UI::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game_UI::update()
{
}

void Game_UI::render()
{
	SDL_RenderClear(renderer);
	//Render Stuff
	SDL_RenderPresent(renderer);
}

void Game_UI::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned";
}
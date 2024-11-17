#include <array>
#include <iostream>
#include "Game.h"
#include <SDL.h>

int main(int argc, char* argv[]) {


	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* window = SDL_CreateWindow("Eter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);

	/*
	while (game is running)
	{
		handle any user input
		update all object eg. position etc
		render changes to the display
	}
	*/

	Game* g = new Game();
	
	g->start();

	delete g;

	return 0;
}
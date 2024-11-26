#include <array>
#include <iostream>
#include "Game.h"
#include <SDL.h>
import Game_UI;

int main(int argc, char* argv[]) {


	Game_UI* game = new Game_UI();
	Game* g = new Game();

	g->start();


	while (game->running()) {
		game->handleEvents();
		game->update();
		game->render();
	}
	/*
	while (game is running)
	{
		handle any user input
		update all object eg. position etc
		render changes to the display
	}
	*/

	delete g;

	game->clean();

	return 0;
}
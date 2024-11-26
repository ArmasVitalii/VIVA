#include <array>
#include <iostream>
#include "Game.h"

int main(int argc, char* argv[]) {

	Game* g = new Game();

	g->start();

	delete g;

	return 0;
}
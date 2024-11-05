#include "Game.h"
#include <array>
#include <iostream>

int main() {

	Game* g = new Game();
	
	g->start();

	delete g;



	return 0;
}
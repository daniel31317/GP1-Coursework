#include <iostream>
#include "GameSource.h"


int main()
{
	GameSource game;
	game.initialiseGame();
	game.gameLoop();
	return 0;
}
#include <iostream>

#include "Game.h"

int main(int argc, char** argv)
{
	std::cout << "Launching Game Instance\n";
	Game gameInstance = Game();
	gameInstance.GameLoop();

	return 0;
}

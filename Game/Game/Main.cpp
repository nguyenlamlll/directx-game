#include "stdafx.h"
#include "Game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	std::unique_ptr<Game> game (new Game(hInstance, nCmdShow));

	if (game->GameInit())
	{
		game->GameRun();
	}

	game->GameEnd();

	game.reset();

	return 0;
}
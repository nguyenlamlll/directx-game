#include "stdafx.h"
#include "Game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Memory leak detecting in debug mode.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	std::unique_ptr<Game> game (new Game(hInstance, nCmdShow));

	if (game->GameInit())
	{
		game->GameRun();
	}

	game->GameEnd();

	game.reset();

	_CrtDumpMemoryLeaks();
	return 0;
}
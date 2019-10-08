#pragma once

#include "resource.h"

#include "Global.h"

#include "KeyboardInput.h"
#include "MouseInput.h"

class Game
{
private:
	void LoadResources();
	int InitWindow();
	int InitDirectX();
	int InitKeyboard();
	int	_nCmdShow;

	static LRESULT CALLBACK WinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	virtual void GameUpdate(float deltaTime);
	virtual void GameRender();
public:
	Game(HINSTANCE hInstance, int nCmdShow);

	bool GameInit();
	void GameRun();
	void GameEnd();
};
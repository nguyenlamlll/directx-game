#pragma once

#include "resource.h"

#include "Global.h"

#include "KeyboardInput.h"
#include "MouseInput.h"

#include "Sprite.h"

class Game
{
private:
	Sprite* m_rightPadSprite;
	Sprite* m_leftPadSprite;
	Sprite* m_ballSprite;
	void setDefaultSpritePositions();

	Sprite* m_newMatchSprite = nullptr;
	Sprite* m_leftWinSprite = nullptr;
	Sprite* m_rightWinSprite = nullptr;

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
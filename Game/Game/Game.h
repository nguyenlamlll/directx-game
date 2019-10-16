#pragma once

#include "resource.h"

#include "Global.h"

#include "KeyboardInput.h"
#include "MouseInput.h"

#include "Sprite.h"
#include "Collision.h"

#include "Ball.h"
#include "Pad.h"

class Game
{
private:
	Ball* m_ball;
	Pad* m_leftPad;
	Pad* m_rightPad;

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
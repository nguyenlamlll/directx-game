#pragma once

#include "resource.h"

#include "Global.h"

#include "Sound.h"

#include "KeyboardInput.h"
#include "MouseInput.h"

#include "Sprite.h"
#include "Collision.h"

#include "Ball.h"
#include "Pad.h"
#include "Player.h"

#include "Grid.h"
#include "SceneManager.h"

#include "PlayScene.h"

class Game
{
private:
	Ball* m_ball;
	Pad* m_leftPad;
	Pad* m_rightPad;
	Pad* m_pad03;
	Pad* m_pad04;
	Player* m_player;
	Grid* grid;

	std::map<int, GameObject*>* listCanCollideWithPlayer;

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
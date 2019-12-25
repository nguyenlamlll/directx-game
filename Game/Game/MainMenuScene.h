#pragma once
#include "Scene.h"

#include "Sprite.h"
#include "Text.h"

#include "KeyboardInput.h"

#include "SceneManager.h"
#include "DungeonScene.h"

class MainMenuScene :
	public Scene
{
private:
	Sprite* m_gameLogo;
	Sprite* m_background;
	Sprite* m_selectionSword;

	Text* m_playText;
	Text* m_optionsText;

	int m_selectionIndex{ 1 };


public:
	MainMenuScene();
	~MainMenuScene();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	virtual void OnKeyDown(int keyCode) override;
	virtual void OnKeyUp(int keyCode) override;

	virtual void ReleaseAll() override;
	virtual void initialize() override;
};


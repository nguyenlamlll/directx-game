#pragma once
#include "Scene.h"

#include "Sprite.h"
#include "Text.h"

#include "KeyboardInput.h"

#include "SceneManager.h"
#include "BossScene.h"
#include "DungeonScene.h"

class LevelCompleteScene :
	public Scene
{
private:
	DWORD start;
	bool m_isAnimationFinished{ false };
	Sprite* m_levelComplete;

	Scene* m_nextScene;

public:
	LevelCompleteScene(Scene* nextScene);
	~LevelCompleteScene();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	virtual void OnKeyDown(int keyCode) override;
	virtual void OnKeyUp(int keyCode) override;

	virtual void ReleaseAll() override;
	virtual void initialize() override;
};


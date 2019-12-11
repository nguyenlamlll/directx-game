#pragma once
#include "Scene.h"
#include "SceneManager.h"
#include "PlayScene.h"

#include "KeyboardInput.h"

class BossScene :
	public Scene
{
private:
	GameMap* m_map;
	Player* m_player;

	std::map<int, GameObject*>* m_listCanCollideWithPlayer;
	Grid* m_grid;

public:
	BossScene();
	~BossScene();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	virtual void OnKeyDown(int keyCode) override;
	virtual void OnKeyUp(int keyCode) override;

	virtual void ReleaseAll() override;

	void loadPlayerConfigurationsFromFile();
	void loadObjectsFromFileToGrid();
};


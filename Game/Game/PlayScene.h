#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Grid.h"

#include "Pad.h"
#include "Ball.h"

#include "GameMap.h"

#include <map>
#include <iostream>
class PlayScene :
	public Scene
{
private:
	Sprite* m_sprite;
	GameMap* m_map;

	std::map<int, GameObject*>* m_objectList;
	std::map<int, GameObject*>* m_listCanCollideWithPlayer;
	Player* m_player;

	Grid* m_grid;

public:
	PlayScene();
	~PlayScene();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	virtual void OnKeyDown(int keyCode) override;
	virtual void OnKeyUp(int keyCode) override;

	virtual void ReleaseAll() override;

	void loadResources();

	void SaveGridToFile();
	void LoadGridFromFile();
};


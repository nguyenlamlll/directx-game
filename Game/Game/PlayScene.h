#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Grid.h"

#include "Pad.h"
#include "Ball.h"
#include "AppleItem.h"
#include "BlueHeartItem.h"
#include "GenieFaceItem.h"
#include "GenieJarItem.h"
#include "RubyItem.h"
#include "Peddler.h"
#include "ForegroundChains.h"

#include "ThinGuard.h"
#include "MustacheGuard.h"
#include "Bat.h"
#include "Skeleton.h"

#include "FloatingBrick.h"
#include "Spike.h"
#include "HangingMorningStar.h"

#include "GameMap.h"
#include "Sound.h"

#include "SceneManager.h"
#include "BossScene.h"

#include <map>
#include <iostream>
class PlayScene :
	public Scene
{
private:
	GameMap* m_map;
	Sprite* m_firstColumn;
	Sprite* m_secondColumn;
	Sprite* m_thirdColumn;
	Sprite* m_fourthColumn;

	std::map<int, GameObject*>* m_objectList;
	std::map<int, GameObject*>* m_listCanCollideWithPlayer;
	Player* m_player;

	Grid* m_grid;
	Grid* m_foregroundGrid;

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


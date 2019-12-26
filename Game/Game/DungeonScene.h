#pragma once
#include "AladdinGlobal.h"
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Grid.h"

#include "ExitDoor.h"
#include "Ground.h"
#include "VerticalWall.h"
#include "ClimbArea.h"

#include "AppleItem.h"
#include "BlueHeartItem.h"
#include "GenieFaceItem.h"
#include "GenieJarItem.h"
#include "RubyItem.h"
#include "Peddler.h"
#include "ForegroundChains.h"
#include "BloodBar.h"

#include "ThinGuard.h"
#include "MustacheGuard.h"
#include "Bat.h"
#include "Skeleton.h"

#include "FloatingBrick.h"
#include "Spike.h"
#include "HangingMorningStar.h"

#include "GameMap.h"
#include "Sound.h"

#include "Boss.h"
#include "Star.h"
#include "Fire.h"

#include "RubyScores.h"
#include "LifeScores.h"
#include "AppleScores.h"
#include "AladdinScores.h"

#include "SceneManager.h"
#include "BossScene.h"
#include "LevelCompleteScene.h"

#include <map>
#include <iostream>
class DungeonScene :
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

	BloodBar* m_blood;
	RubyScores* m_rubyScore;
	LifeScores* m_lifeScore;
	AppleScores* m_appleScore;
	AladdinScores* m_aladdinScore;

	Grid* m_grid;
	Grid* m_foregroundGrid;

public:
	DungeonScene();
	~DungeonScene();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	virtual void OnKeyDown(int keyCode) override;
	virtual void OnKeyUp(int keyCode) override;

	virtual void ReleaseAll() override;
	virtual void initialize() override;

	void loadResources();

	void SaveGridToFile();
	void LoadGridFromFile();
	void loadWallsFromFileToGrid();
};


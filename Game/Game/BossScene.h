#pragma once
#include "Scene.h"
#include "SceneManager.h"
#include "DungeonScene.h"

#include "KeyboardInput.h"

#include "Boss.h"
#include "VerticalWall.h"

class Player;
class BossScene :
	public Scene
{
private:
	GameMap* m_map;
	Player* m_player;

	std::map<int, GameObject*>* m_listCanCollideWithPlayer;
	Grid* m_grid;

	BloodBar* m_blood;
	RubyScores* m_rubyScore;
	LifeScores* m_lifeScore;
	AppleScores* m_appleScore;
	AladdinScores* m_aladdinScore;

public:
	BossScene();
	~BossScene();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	virtual void OnKeyDown(int keyCode) override;
	virtual void OnKeyUp(int keyCode) override;

	virtual void ReleaseAll() override;
	virtual void initialize() override;

	void loadPlayerConfigurationsFromFile();
	void loadObjectsFromFileToGrid();
};


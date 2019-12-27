#pragma once
#include "Scene.h"
#include "SceneManager.h"
#include "DungeonScene.h"

#include "KeyboardInput.h"

#include "Boss.h"
#include "VerticalWall.h"

#include "AladdinDeath.h"

#include "AladdinGlobal.h"

class Player;
class BossScene :
	public Scene
{
private:
	AladdinDeath* m_aladdinDeathOverlay;
	bool m_isAladdinDeathOverlaying{ false };
	DWORD m_overlayTimer{ 0 }, m_waiter;

	GameMap* m_map;
	Player* m_player;

	std::map<int, GameObject*>* m_listCanCollideWithPlayer;
	Grid* m_grid;

	BloodBar* m_blood;
	RubyScores* m_rubyScore;
	LifeScores* m_lifeScore;
	AppleScores* m_appleScore;
	AladdinScores* m_aladdinScore;

	DWORD m_generateTimer;
	bool m_shouldGenerateApples{ false };
	int m_generatedAppleCount{ 1000 };

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
	
	// When the user runs out of apple in this scene, the map automatically generate new apples.
	void generateApples();
};


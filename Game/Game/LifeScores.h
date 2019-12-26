#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Sprite.h"
#include "Player.h"

class LifeScores : public GameObject
{
protected:
	int currentScores;
	//int test;
	Animation* m_imageIcon;
	Animation* m_imageScore;

	bool ischange;

	Player* m_player;

public:
	LifeScores(float x, float y, float width, float height);
	~LifeScores();
	void increaseScores();
	void abstractScores();
	void changeDisplayScores();

	int getScore();
	void setScore(int value);

	void Update(float deltaTime);
	void Draw();

	void attachPlayer(Player* player);
};
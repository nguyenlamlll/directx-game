#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Sprite.h"
#include "Player.h"

class AladdinScores : public GameObject
{
protected:
	int currentScores;
	//int test;
	Animation* m_imageOne;
	Animation* m_imageTen;
	Animation* m_imageHundred;
	Animation* m_imageThousand;
	Animation* m_imageTenThousand;

	bool changing, changeTen, changeHundred, changeThousand;
	int tenThousand, thousand, hundred, ten, one;

	Player* m_player;

public:
	AladdinScores(float x, float y, float width, float height);
	~AladdinScores();
	void increaseScores(int value);
	void styleBeforeChange();
	void changeDisplayScores();
	void setNumberScores();

	void Update(float deltaTime);
	void Draw();

	int getScore();
	void setScore(int value);

	void attachPlayer(Player* player);
};

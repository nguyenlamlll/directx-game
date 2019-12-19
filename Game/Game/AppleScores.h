#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Sprite.h"

class AppleScores : public GameObject
{
protected:
	int currentScores;
	//int test;
	Animation* m_imageIcon;
	Animation* m_imageOne;
	Animation* m_imageTen;
	Animation* m_imageHundred;

	bool ischange;
public:
	AppleScores(float x, float y, float width, float height);
	~AppleScores();
	void increaseScores();
	void abstractScores();
	void changeDisplayScores();
	void resetLifeAladdin();
	int getScore();

	void Update(float deltaTime);
	void Draw();
};
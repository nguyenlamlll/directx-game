#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Sprite.h"

class RubyScores : public GameObject
{
protected:
	int currentScores;
	//int test;
	Animation* m_imageIcon;
	Animation* m_imageOne;
	Animation* m_imageTen;
	Animation* m_imageHundred;
public:
	RubyScores(float x, float y, float width, float height);
	~RubyScores();
	void increaseScores();
	void abstractScores(int value);
	void changeDisplayScores();

	void Update(float deltaTime);
	void Draw();

};

#pragma once
#include "GameObject.h"
#include "Sprite.h";
#include "Pad.h"

class Ball : public GameObject
{
private:
	Sprite* m_ballSprite;

	float ballSpeed = 0.f;
	float ballVerticalSpeed = 0.f;

	Pad* m_rightPad = nullptr; 
	Pad* m_leftPad = nullptr;

	bool isFirstStarted;
public:
	Ball(float x, float y, float width, float height, LPCWSTR spritePath);
	~Ball();

	void setRandomInitialSpeed(float deltaTime);
	void assignPadsCanCollideBall(Pad*, Pad*);

	Box GetBoundingBox();

	void Update(float deltaTime);
	void Draw();
};


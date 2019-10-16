#pragma once
#include "Collision.h"

class GameObject
{
protected:
	float x, y;
	float width, height;
	float vx, vy;
public:
	GameObject();
	GameObject(float x, float y, float width, float height);
	virtual ~GameObject();

	virtual Box GetBoundingBox();

	virtual void Update(float deltaTime);
	virtual void Draw();

};


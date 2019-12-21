#pragma once
#include "GameObject.h"
#include "Sprite.h"
class ExitDoor :
	public GameObject
{
private:
	Sprite* m_sprite;
public:
	ExitDoor(float x, float y, float width, float height);
	~ExitDoor();

	Box GetBoundingBox();

	void Update(float deltaTime);
	void Draw();
};


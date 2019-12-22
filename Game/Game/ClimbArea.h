#pragma once
#include "GameObject.h"
#include "Sprite.h"

class ClimbArea :
	public GameObject
{
protected:
	Sprite* m_debugSprite;
	bool m_isDebugVisible{ false };
public:
	ClimbArea(float x, float y, float width, float height, bool isDebug);
	~ClimbArea();

	void setIsDebugVisible(bool value);

	Box GetBoundingBox();

	void Update(float deltaTime);
	void Draw();
};


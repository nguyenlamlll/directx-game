#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include <string.h>
class VerticalWall :
	public GameObject
{
private:
	Sprite* m_sprite;
	Sprite* m_debugSprite;
	Sprite* m_realSprite;
	bool m_isDebugVisible{ false };
public:
	VerticalWall(std::string spriteName, float x, float y, float width, float height, float scaleX, float scaleY, bool isDebug);
	~VerticalWall();

	void setIsDebugVisible(bool value);

	Box GetBoundingBox();

	void Update(float deltaTime);
	void Draw();
};


#pragma once
#include "GameObject.h"
#include "Sprite.h"
class Ground:
	public GameObject
{
private:
	Sprite* m_sprite;
	Sprite* m_debugSprite;
	Sprite* m_realSprite;
	bool m_isDebugVisible{ false };
public:
	Ground(float x, float y, float width, float height, float scaleX, float scaleY, bool isDebug);
	~Ground();

	void setIsDebugVisible(bool value);

	Box GetBoundingBox();

	void Update(float deltaTime);
	void Draw();
};


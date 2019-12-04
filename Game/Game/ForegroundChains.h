#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "KeyboardInput.h"
class ForegroundChains :
	public GameObject
{
private:
	Sprite* m_sprite;
public:
	ForegroundChains(float x, float y, float width, float height, float scaleX, float scaleY);
	~ForegroundChains();

	void Update(float deltaTime); 
	void Draw();

};


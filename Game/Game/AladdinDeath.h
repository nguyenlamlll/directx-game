#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "Animation.h"
#include "Sound.h"
class AladdinDeath :
	public GameObject
{
protected:
	Sprite* m_background;
	Animation* m_animation;
	int m_boxingBellPlayCount{ 0 };
	DWORD m_timer;
public:
	AladdinDeath();
	~AladdinDeath();
	
	void reset();
	void Update(float deltaTime);
	void Draw();
};


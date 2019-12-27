#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "Animation.h"
#include "Sound.h"
class AladdinDeath :
	public GameObject
{
private:
	bool isChange;
protected:
	Sprite* m_background;
	Animation* m_animation;
	Animation* m_animation_aladdinDied;
	Animation* m_animation_aladdinDiedWithGenie;
	Animation* m_animation_monkey;
	int m_boxingBellPlayCount{ 0 };
	DWORD m_timer;
public:
	AladdinDeath();
	~AladdinDeath();
	
	void reset();
	void Update(float deltaTime);
	void Draw();
};


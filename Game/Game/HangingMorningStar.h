#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "Animation.h"
#include "Spike.h"

class HangingMorningStar : public GameObject
{
protected:
	Animation* image;
	Animation* m_morningStarInside;
	Animation* m_morningStarOutside;

	States state;
	StatusDamage status;

	// value check reset load animation
	DWORD last_time, start_wait;
public:
	HangingMorningStar(float x, float y, float width, float height, int indexFrame);
	~HangingMorningStar();

	Box GetBoundingBox();

	D3DXVECTOR2 getVelocity();

	void Update(float deltaTime);
	void OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime);
	void Draw();

	void ChangeDirection();

	StatusDamage getStatus();

	bool m_isAttackingHit{ false };
};

#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "Animation.h"
#include "Sound.h"
#include "FloatingBrick.h"

namespace _StatusDamage {
	enum StatusDamage {
		Damage,
		NotDamage
	};
}
using namespace _StatusDamage;

class Spike : public GameObject
{
protected:
	StatusDamage status;
	States state;

	Animation* image;
	Animation* m_spikeInside;
	Animation* m_spikeOutside;

	// value check reset load animation
	DWORD last_time, start_wait;

	bool m_isSoundPlayed{ false };

public:
	Spike(float x, float y, float width, float height, int type);
	~Spike();

	Box GetBoundingBox();

	D3DXVECTOR2 getVelocity();

	void Update(float deltaTime);
	void OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime);
	void Draw();

	void ChangeDirection();

	StatusDamage getStatus();

	bool m_isAttackingHit{ false };
};

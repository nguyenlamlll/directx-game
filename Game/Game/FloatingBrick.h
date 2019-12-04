#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "Animation.h"

namespace _States {
	enum States {
		GoInside,
		GoOutside
	};
}
using namespace _States;

enum Status {
	Allow,
	NotAllow
};

class FloatingBrick : public GameObject
{
protected:
	Status status;
	States state;

	Animation* image;
	Animation* m_brickInside;
	Animation* m_brickOutside;

	// value check reset load animation
	DWORD last_time, start_wait;
public:
	FloatingBrick(float x, float y, float width, float height, int type);
	~FloatingBrick();

	Box GetBoundingBox();

	D3DXVECTOR2 getVelocity();

	void Update(float deltaTime);
	void OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime);
	void Draw();

	void ChangeDirection();

	Status getStatus();
};
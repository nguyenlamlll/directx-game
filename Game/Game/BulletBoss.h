#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Sprite.h"

class BulletBoss : public GameObject
{
protected:
	bool isDead;
public:
	BulletBoss(float x, float y, float width, float height, Tag tag);
	~BulletBoss();

	Box GetBoundingBox();
	D3DXVECTOR2 getVelocity();
	void Update(float deltaTime) {}
	void Draw() {}
	void OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime) {}

	bool getIsDead();

};


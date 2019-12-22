#pragma once
#include "Player.h"
#include "Boss.h"
#include "BulletBoss.h"

class Boss;

class Fire : public BulletBoss
{
protected:
	Animation* m_image;
	bool isDied;

	float m_anchorX;

	Boss* m_boss;

	bool m_isAttackingHit{ false };

public:
	Fire(float x, float y, float width, float height, Boss* boss);
	~Fire();

	Box GetBoundingBox();
	D3DXVECTOR2 getVelocity();
	void Update(float deltaTime);
	void Draw();

	void igniteAction();

	void OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime);
	void OnCollision(GameObject* colliableObject, float deltaTime);
};

#pragma once
#include "Player.h"
#include "Boss.h"

class Fire : public GameObject
{
protected:
	Animation* m_image;

	bool isDead;
	bool isDied;

	float m_anchorX;

	//Boss* m_boss;

public:
	Fire(float x, float y, float width, float height, bool isFacingRight);
	~Fire();

	Box GetBoundingBox();
	D3DXVECTOR2 getVelocity();
	void Update(float deltaTime);
	void Draw();

	void igniteAction();

	void OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime);

};

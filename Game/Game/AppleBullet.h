#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Sprite.h"

enum BulletAppleStatus {
	BulletAppleFlying,
	BulletAppleBurst,
	BulletAppleBurstBoss,
};

class PlayerState;

class AppleBullet : public GameObject
{

protected:
	BulletAppleStatus  m_state;
	Animation* m_image;
	Animation* m_imageFlying;
	Animation* m_imageBurst;
	Animation* m_imageBurstBoss;
	float achorY;
	bool isDead;

public:

	AppleBullet(float x, float y, float width, float height, bool isToRight);
	
	~AppleBullet();
	
	Box GetBoundingBox();

	D3DXVECTOR2 getVelocity();

	void Update(float deltaTime);
	void OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime);
	void Draw();

	void FlyingAction();
	void BurstAction();
	void BurstBossAction();
	
	void checkPositionBullet();
	bool getIsDead();
};


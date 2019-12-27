#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Sprite.h"
#include "MustacheGuard.h"
#include "Skeleton.h"

enum BoneStatus {
	BoneFlying,
	BoneBurst,
};

class BoneBullet : public GameObject
{

protected:
	BoneStatus  m_state;
	Animation* m_image;
	Animation* m_imageFlying;
	Animation* m_imageBurst;
	bool isDead;
	float anchorX, anchorY;
	int line;
	// One apple can only deal damage one time. After this variable is set to true. Damage no longer applies.
public:

	BoneBullet(float x, float y, float width, float height, int line);

	~BoneBullet();

	Box GetBoundingBox();

	D3DXVECTOR2 getVelocity();

	void Update(float deltaTime);
	void OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime);
	void OnCollision(GameObject* colliableObject, float deltaTime);
	void Draw();

	void FlyingAction();
	void BurstAction();

	void checkPositionBullet();
	bool getIsDead();
};


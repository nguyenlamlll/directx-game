#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Sprite.h"
#include "Player.h"
#include "Health.h"

#include <unordered_map>

enum SkeletonState {
	SkeletonCrawl,
	SkeletonTransform,
	SkeletonBurst,
	SkeletonAttact
};

class Skeleton : 
	public GameObject,
	public Health
{
protected:
	SkeletonState m_state;
	Animation* m_image;
	Animation* m_imageCrawl;
	Animation* m_imageTransform;
	Animation* m_imageBurst;
	// value check reset load animation
	DWORD m_lastTime, m_startWait;
	Player* m_player;

	bool isDead, isUsed;
public:
	Skeleton(float x, float y, float width, float height, bool isFacingRight);
	~Skeleton();
	virtual void deinitialize() override;

	Box GetBoundingBox();
	Box GetBoundingBoxForApple();
	D3DXVECTOR2 getVelocity();
	void Update(float deltaTime);
	void Draw();

	void OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime);
	void OnCollision(GameObject* colliableObject, float deltaTime);
	void attachPlayer(Player* player);
	void checkPositionWithPlayer();

	void ResetAction();
	void TransformAction();
	void BurstAction();
	void AttactAction();

};

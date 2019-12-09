#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Sprite.h"
#include "Player.h"

#include <unordered_map>

enum SkeletonState {
	SkeletonCrawl,
	SkeletonTransform,
	SkeletonBurst,
	SkeletonAttact
};

class Skeleton : public GameObject
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

	bool isDead;
	// has been used ? true = not used || false = used
	bool isUsed;
	bool isDied;
public:
	Skeleton(float x, float y, float width, float height, bool isFacingRight);
	~Skeleton();

	Box GetBoundingBox();
	D3DXVECTOR2 getVelocity();
	void Update(float deltaTime);
	void Draw();

	void OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime);
	void attachPlayer(Player* player);
	void checkPositionWithPlayer();

	void ResetAction();
	void TransformAction();
	void BurstAction();
	void AttactAction();

	//get state
	SkeletonState getState();
};

#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Sprite.h"
#include "Player.h"
#include "Health.h"

#include <unordered_map>

enum BatState {
	BatSwing,
	BatMoving,
	BatFling,
	BatBurst
};
class Bat :
	public GameObject, 
	public Health
{
protected:
	DWORD start;

	BatState m_state;

	Player* m_player;

	Animation* m_image;
	Animation* m_imageSwing;
	Animation* m_imageMoving;
	Animation* m_imageFling;
	Animation* m_imageBurst;

	float m_originalX, m_originalY;
	float m_limit_left, m_limit_top, m_limit_right;
	// anchor point
	float m_anchorX, m_anchorY;
	// flag up-down
	bool m_isFacingUp;

	bool isDead;
	// has been used ? true = not used || false = used
	bool isUsed;
	bool isDied;

	bool m_isAttackingHit{ false };

public:
	Bat(float x, float y, float width, float height, float limit_left, float limit_right);
	~Bat();

	Box GetBoundingBox();
	Box GetBoundingBoxForApple();
	D3DXVECTOR2 getVelocity();
	void Update(float deltaTime);
	void Draw();

	void checkPositionWithPlayer();
	void attachPlayer(Player* player);

	void OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime);
	void OnCollision(GameObject* colliableObject, float deltaTime);
	
	void ResetAction();
	void MovingAction();
	void FlingAction();
	void BurstAction();

	//get state
	BatState getState();
};
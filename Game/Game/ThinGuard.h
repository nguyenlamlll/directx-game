#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Player.h"
#include "Health.h"

#include <unordered_map>

enum class ThinGuardStates {
	Standing,
	Moving,
	Attacking,
	BeingHit,
	ThinBurst,
};

class ThinGuard :
	public GameObject,
	public Health
{
private:
	void checkAndUpdateDirection();
	bool isPlayerOnTheLeft();

protected:
	Player* m_player = nullptr;
	float speed{ 0.15f };
	D3DXVECTOR2 m_initialPosition;

	bool m_isBeingHit{ false };
	bool m_isAttackingHit{ false };
	bool isDead;

	int m_attackRange{ 90 };
	int m_moveRange{ 200 };

public:
	Animation* m_currentAnimation;
	std::unordered_map<ThinGuardStates, Animation*> m_animations;
	ThinGuardStates m_currentState; 

	ThinGuard(float x, float y, float width, float height);
	~ThinGuard();


	void attachPlayer(Player* player);
	void checkPositionWithPlayer();

	// Player calls this function when attacking the guard. The guard will turn itself into "being-hit" state.
	void isHit();

	Box GetBoundingBox();
	Box GetBoundingBoxForApple();

	void Update(float deltaTime);
	void OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime);
	void OnCollision(GameObject* colliableObject, float deltaTime);
	void Draw();

	void setAttackRange(int value);
	void setMoveRange(int value);
};


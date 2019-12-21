#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Player.h"
#include "Health.h"

#include <unordered_map>

enum class MustacheGuardStates {
	Standing,
	Moving,
	MovingOnLava,
	Attacking1,
	Attacking2,
	BeingHit,
};

class MustacheGuard :
	public GameObject,
	public Health
{
private:
	void checkAndUpdateDirection();
	bool isPlayerOnTheLeft();

protected:
	Player* m_player = nullptr;
	float speed{ 0.1f };
	bool m_isBeingHit{ false };
	bool m_isAttackingHit{ false };

	D3DXVECTOR2 m_initialPosition;


public:
	Animation* m_currentAnimation;
	MustacheGuardStates m_currentState;
	std::unordered_map<MustacheGuardStates, Animation*> m_animations;

	MustacheGuard(float x, float y, float width, float height);
	~MustacheGuard();

	void attachPlayer(Player* player);
	void checkPositionWithPlayer();

	// Player calls this function when attacking the guard. The guard will turn itself into "being-hit" state.
	void isHit();

	Box GetBoundingBox();

	void Update(float deltaTime);
	void OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime);
	void OnCollision(GameObject* colliableObject, float deltaTime);
	void Draw();
};


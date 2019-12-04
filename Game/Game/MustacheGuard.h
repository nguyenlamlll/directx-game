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
protected:
	Player* m_player = nullptr;
public:
	Animation* m_currentAnimation;
	MustacheGuardStates m_currentState;
	std::unordered_map<MustacheGuardStates, Animation*> m_animations;

	MustacheGuard(float x, float y, float width, float height);
	~MustacheGuard();

	void attachPlayer(Player* player);
	void checkPositionWithPlayer();

	Box GetBoundingBox();

	void Update(float deltaTime);
	void OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime);
	void Draw();
};


#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Player.h"

#include <unordered_map>

enum class ThinGuardStates {
	Standing,
	Running,
	Attacking,
	BeingHit
};

class ThinGuard :
	public GameObject
{
protected:
	Player* m_player = nullptr;
public:
	Animation* m_currentAnimation;
	std::unordered_map<ThinGuardStates, Animation*> m_animations;
	ThinGuardStates m_currentState; 

	ThinGuard();
	ThinGuard(float x, float y, float width, float height);
	~ThinGuard();


	void attachPlayer(Player* player);
	void checkPositionWithPlayer();

	Box GetBoundingBox();

	void Update(float deltaTime);
	void OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime);
	void Draw();

};


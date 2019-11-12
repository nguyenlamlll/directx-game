#pragma once
#include "GameObject.h"

enum PlayerStates {
	Standing,
	Moving,
	Jumping
};
class Player;
class PlayerState
{
protected:
	Player* m_player;

public:
	PlayerState() {}
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;
	virtual PlayerStates GetState() = 0;
	virtual void OnCollision(GameObject* entity, float deltaTime) = 0;
};


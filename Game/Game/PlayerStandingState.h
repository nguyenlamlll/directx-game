#pragma once
#include "PlayerState.h"
#include "Player.h"
#include "Animation.h"

class PlayerStandingState : public PlayerState
{
private:
	Player* m_player;
	Animation* m_animation;
	Animation* m_animationStand;
	Animation* m_animationStandLookAround;

	float m_idleTime = 0.0f;

	bool m_isIdling01 = false;

public:
	PlayerStandingState(Player* player, Animation* animation);
	~PlayerStandingState();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	virtual PlayerStates GetState() override;
	virtual void OnCollision(GameObject* entity, float deltaTime) override;
};


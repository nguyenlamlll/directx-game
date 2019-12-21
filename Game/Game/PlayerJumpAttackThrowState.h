#pragma once

#include "PlayerState.h"
#include "Player.h"
#include "Animation.h"


class PlayerJumpAttackThrowState : public PlayerState
{
private:
	Player* m_player;
	Animation* m_animation;
	float m_initialY;
	float m_travelledJumpDistance;
	float m_longestJumpDistance;

public:
	PlayerJumpAttackThrowState(Player* player, Animation* animation);
	~PlayerJumpAttackThrowState();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	virtual PlayerStates GetState() override;
	virtual void PreCollision(GameObject* entity, float deltaTime) override;
	virtual void OnCollision(GameObject* entity, float deltaTime) override;

	virtual void createAppleBullet() override;
};


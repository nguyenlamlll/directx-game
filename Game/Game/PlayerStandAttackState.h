
#pragma once

#include "PlayerState.h"
#include "Player.h"
#include "Animation.h"

#include "MustacheGuard.h"
#include "ThinGuard.h"

class PlayerStandAttackState : public PlayerState
{
private:
	Player* m_player;
	Animation* m_animation;

	bool m_isFinished = false;

	// Aladdin in attack state can only hit one enemy one time. Use this variable to track it.
	bool isAttackingHit = false;

public:
	PlayerStandAttackState(Player* player, Animation* animation);
	~PlayerStandAttackState();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	virtual PlayerStates GetState() override;
	virtual void OnCollision(GameObject* entity, float deltaTime) override;
};


#pragma once

#include "PlayerState.h"
#include "Player.h"
#include "Animation.h"

class PlayerStandAttackState : public PlayerState
{
private:
	Player* m_player;
	Animation* m_animation;

	bool m_isFinished = false;
public:
	PlayerStandAttackState(Player* player, Animation* animation);
	~PlayerStandAttackState();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	virtual PlayerStates GetState() override;
	virtual void OnCollision(GameObject* entity, float deltaTime) override;
};

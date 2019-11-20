
#pragma once

#include "PlayerState.h"
#include "Player.h"
#include "Animation.h"

class PlayerSwingAttackState : public PlayerState
{
private:
	Player* m_player;
	Animation* m_animation;
public:
	PlayerSwingAttackState(Player* player, Animation* animation);
	~PlayerSwingAttackState();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	virtual PlayerStates GetState() override;
	virtual void OnCollision(GameObject* entity, float deltaTime) override;
};


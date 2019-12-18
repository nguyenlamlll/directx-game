
#pragma once

#include "PlayerState.h"
#include "Player.h"
#include "Animation.h"

class PlayerStandAttackThrowState : public PlayerState
{
private:
	Player* m_player;
	Animation* m_animation;
public:
	PlayerStandAttackThrowState(Player* player, Animation* animation);
	~PlayerStandAttackThrowState();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	virtual PlayerStates GetState() override;
	virtual void PreCollision(GameObject* entity, float deltaTime) override;
	virtual void OnCollision(GameObject* entity, float deltaTime) override;
};

#pragma once

#include "PlayerState.h"
#include "Player.h"
#include "Animation.h"

class PlayerSitDownAttackThrowState : public PlayerState
{
private:
	Player* m_player;
	Animation* m_animation;
public:
	PlayerSitDownAttackThrowState(Player* player, Animation* animation);
	~PlayerSitDownAttackThrowState();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	virtual PlayerStates GetState() override;
	virtual void PreCollision(GameObject* entity, float deltaTime) override;
	virtual void OnCollision(GameObject* entity, float deltaTime) override;
};

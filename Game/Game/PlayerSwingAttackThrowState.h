
#pragma once

#include "PlayerState.h"
#include "Player.h"
#include "Animation.h"

class PlayerSwingAttackThrowState : public PlayerState
{
private:
	Player* m_player;
	Animation* m_animation;
public:
	PlayerSwingAttackThrowState(Player* player, Animation* animation);
	~PlayerSwingAttackThrowState();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	virtual PlayerStates GetState() override;
	virtual void OnCollision(GameObject* entity, float deltaTime) override;

	virtual void createAppleBullet() override;
};


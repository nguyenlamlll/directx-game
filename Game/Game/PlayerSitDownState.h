#pragma once

#pragma once
#include "PlayerState.h"
#include "Player.h"
#include "Animation.h"

class PlayerSitDownState : public PlayerState
{
private:
	Player* m_player;
	Animation* m_animation;
public:
	PlayerSitDownState(Player* player, Animation* animation);
	~PlayerSitDownState();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	virtual PlayerStates GetState() override;
	virtual void OnCollision(GameObject* entity, float deltaTime) override;
};


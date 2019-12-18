#pragma once

#include "PlayerState.h"
#include "Player.h"
#include "Animation.h"

class PlayerJumpMovingState : public PlayerState
{
private:
	Player* m_player;
	Animation* m_animation;

	float m_initialCameraY;

	float m_initialY;

	float m_travelledJumpDistance;
	float m_longestJumpDistance;

	bool isFalling();

public:
	PlayerJumpMovingState(Player* player, Animation* animation);
	~PlayerJumpMovingState();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	virtual PlayerStates GetState() override;
	virtual void PreCollision(GameObject* entity, float deltaTime) override;
	virtual void OnCollision(GameObject* entity, float deltaTime) override;

	float getInitialY();
	float getTravelledJumpDistance();
	float getLongestJumpDistance();
};
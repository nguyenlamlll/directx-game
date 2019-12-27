#pragma once

#include "PlayerState.h"
#include "Player.h"
#include "Animation.h"
#include "FloatingBrick.h"
#include "Ground.h"
#include "ClimbArea.h"
#include "PlayerInputConfigurations.h"

class PlayerJumpStandState : public PlayerState
{
private:
	Player* m_player;
	Animation* m_animation;

	float m_initialCameraY;

	float m_initialY;
	
	float m_travelledJumpDistance;
	float m_longestJumpDistance;

	bool isFalling();

	// If player stands inside a climb area. That area reference will be added here (in PreCollision) and be passed to Climbing state in Update.
	ClimbArea* m_climbArea;

public:
	PlayerJumpStandState(Player* player, Animation* animation);
	~PlayerJumpStandState();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	virtual PlayerStates GetState() override;
	virtual void PreCollision(GameObject* entity, float deltaTime) override;
	virtual void OnCollision(GameObject* entity, float deltaTime) override;

	float getInitialY();
	void setTravelledJumpDistance(float value);
	float getTravelledJumpDistance();
	float getLongestJumpDistance();
};
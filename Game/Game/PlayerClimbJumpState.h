#pragma once
#include "PlayerState.h"
#include "Player.h"
#include "Animation.h"
#include "PlayerInputConfigurations.h"

class PlayerClimbJumpState :
	public PlayerState
{
private:
	Player* m_player;
	Animation* m_animation;
	ClimbArea* m_climbingArea;

	float m_initialY;
	float m_initialCameraY;

	float m_travelledJumpDistance;
	float m_longestJumpDistance;

	bool isFalling();

public:
	PlayerClimbJumpState(Player* player, Animation* animation);
	~PlayerClimbJumpState();

	// Attach the climb area which the current state is climbing inside.
	void attachClimbArea(ClimbArea* climbArea);

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


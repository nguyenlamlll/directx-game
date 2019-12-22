#pragma once
#include "PlayerState.h"
#include "Player.h"
#include "Animation.h"
#include "ClimbArea.h"

class PlayerClimbState : public PlayerState
{
private:
	Player* m_player;
	Animation* m_animation;
	ClimbArea* m_climbingArea;
public:
	PlayerClimbState(Player* player, Animation* animation);
	~PlayerClimbState();

	// Attach the climb area which the current state is climbing inside.
	void attachClimbArea(ClimbArea* climbArea);

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	virtual PlayerStates GetState() override;
	virtual void PreCollision(GameObject* entity, float deltaTime) override;
	virtual void OnCollision(GameObject* entity, float deltaTime) override;
};


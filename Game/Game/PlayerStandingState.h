#pragma once
#include "PlayerState.h"
#include "Player.h"
#include "Animation.h"

#include "ClimbArea.h"

class PlayerStandingState : public PlayerState
{
private:
	Player* m_player;
	Animation* m_animation;
	Animation* m_animationStand;
	Animation* m_animationStandLookAround;

	float m_idleTime = 0.0f;

	bool m_isIdling01 = false;

	// If player stands inside a climb area. That area reference will be added here (in PreCollision) and be passed to Climbing state in Update.
	ClimbArea* m_climbArea;

public:
	PlayerStandingState(Player* player, Animation* animation, Animation* standAndLookAroundAnimadtion);
	~PlayerStandingState();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	virtual PlayerStates GetState() override;
	virtual void PreCollision(GameObject* entity, float deltaTime) override;
	virtual void OnCollision(GameObject* entity, float deltaTime) override;
};


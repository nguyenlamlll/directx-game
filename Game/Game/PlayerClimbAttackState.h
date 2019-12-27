#pragma once
#include "PlayerState.h"
#include "Player.h"
#include "Animation.h"

class PlayerClimbAttackState :
	public PlayerState
{
private:
	Player* m_player;
	Animation* m_animation;

	ClimbArea* m_climbingArea;

	// Aladdin in attack state can only hit one enemy one time. Use this variable to track it.
	bool m_isAttackingHit{ false };

public:
	PlayerClimbAttackState(Player* player, Animation* animation);
	~PlayerClimbAttackState();

	// Attach the climb area which the current state is climbing inside.
	void attachClimbArea(ClimbArea* climbArea);

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	virtual PlayerStates GetState() override;
	virtual void PreCollision(GameObject* entity, float deltaTime) override;
	virtual void OnCollision(GameObject* entity, float deltaTime) override;
};


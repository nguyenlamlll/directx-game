#pragma once
#include "PlayerState.h"
#include "Player.h"

#include "Bat.h"
#include "Skeleton.h"

#include "Animation.h"
class PlayerMoveAttackState : public PlayerState
{
private:
	Player* m_player;
	Animation* m_animation;

	bool isAttackingHit{ false };
public:
	PlayerMoveAttackState(Player* player, Animation* animation);
	~PlayerMoveAttackState();


	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	virtual PlayerStates GetState() override;
	virtual void PreCollision(GameObject* entity, float deltaTime) override;
	virtual void OnCollision(GameObject* entity, float deltaTime) override;
};


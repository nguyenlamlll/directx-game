#pragma once
#include "PlayerState.h"
#include "Player.h"
#include "VerticalWall.h"
#include "Animation.h"
class PlayerMovingState : public PlayerState
{
private:
	Player* m_player;
	Animation* m_animation;
public:
	PlayerMovingState(Player* player, Animation* animation);
	~PlayerMovingState();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	virtual PlayerStates GetState() override;
	virtual void PreCollision(GameObject* entity, float deltaTime) override;
	virtual void OnCollision(GameObject* entity, float deltaTime) override;
};


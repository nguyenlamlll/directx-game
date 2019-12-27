#pragma once
#include "PlayerState.h"
#include "Player.h"
#include "Animation.h"
#include "ClimbArea.h"
#include "PlayerInputConfigurations.h"

class PlayerClimbThrowState :
	public PlayerState
{
private:
	Player* m_player;
	Animation* m_animation;

	ClimbArea* m_climbArea;
	bool m_isAppleThrowed{ false };

public:
	PlayerClimbThrowState(Player* player, Animation* animation);
	~PlayerClimbThrowState();

	void attachClimbArea(ClimbArea* area);

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	virtual PlayerStates GetState() override;
	virtual void PreCollision(GameObject* entity, float deltaTime) override;
	virtual void OnCollision(GameObject* entity, float deltaTime) override;
	virtual void createAppleBullet() override;
};


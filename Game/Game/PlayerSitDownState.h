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
	
	// Is completely sat down or now. Set this to true to set animation to sat down frame.
	bool m_isFixedSatDown{ false };

public:
	PlayerSitDownState(Player* player, Animation* animation, bool isFixedSatDown);
	~PlayerSitDownState();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	virtual PlayerStates GetState() override;
	virtual void PreCollision(GameObject* entity, float deltaTime) override;
	virtual void OnCollision(GameObject* entity, float deltaTime) override;

	void setIsFixedSittingDown(bool value);
	bool isSatDown();
};


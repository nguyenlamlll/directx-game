

#include "stdafx.h"
#include "PlayerClimbState.h"

PlayerClimbState::PlayerClimbState(Player* player, Animation* animation)
{
	m_player = player;
	m_animation = animation;
}


PlayerClimbState::~PlayerClimbState()
{
}

void PlayerClimbState::Update(float deltaTime)
{
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);
	m_animation->Update(deltaTime);
}

void PlayerClimbState::Draw()
{
	m_animation->Draw();
}

PlayerStates PlayerClimbState::GetState()
{
	return PlayerStates::Climb;
}

void PlayerClimbState::OnCollision(GameObject* entity, float deltaTime)
{
}

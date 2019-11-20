#include "stdafx.h"
#include "PlayerMovingStopState.h"


PlayerMovingStopState::PlayerMovingStopState(Player* player, Animation* animation)
{
	m_player = player;
	m_animation = animation;
}


PlayerMovingStopState::~PlayerMovingStopState()
{
}

void PlayerMovingStopState::Update(float deltaTime)
{
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);
	m_animation->Update(deltaTime);
}

void PlayerMovingStopState::Draw()
{
	m_animation->Draw();
}

PlayerStates PlayerMovingStopState::GetState()
{
	return PlayerStates::MovingStop;
}

void PlayerMovingStopState::OnCollision(GameObject* entity, float deltaTime)
{
}

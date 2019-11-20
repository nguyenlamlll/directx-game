#include "stdafx.h"
#include "PlayerSwingStopState.h"

PlayerSwingStopState::PlayerSwingStopState(Player* player, Animation* animation)
{
	m_player = player;
	m_animation = animation;
}


PlayerSwingStopState::~PlayerSwingStopState()
{
}

void PlayerSwingStopState::Update(float deltaTime)
{
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);
	m_animation->Update(deltaTime);
}

void PlayerSwingStopState::Draw()
{
	m_animation->Draw();
}

PlayerStates PlayerSwingStopState::GetState()
{
	return PlayerStates::SwingStop;
}

void PlayerSwingStopState::OnCollision(GameObject* entity, float deltaTime)
{
}
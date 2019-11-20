#include "stdafx.h"
#include "PlayerSwingState.h"

PlayerSwingState::PlayerSwingState(Player* player, Animation* animation)
{
	m_player = player;
	m_animation = animation;
}


PlayerSwingState::~PlayerSwingState()
{
}

void PlayerSwingState::Update(float deltaTime)
{
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);
	m_animation->Update(deltaTime);
}

void PlayerSwingState::Draw()
{
	m_animation->Draw();
}

PlayerStates PlayerSwingState::GetState()
{
	return PlayerStates::Swing;
}

void PlayerSwingState::OnCollision(GameObject* entity, float deltaTime)
{
}
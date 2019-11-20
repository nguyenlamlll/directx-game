#include "stdafx.h"
#include "PlayerFallingState.h"

PlayerFallingState::PlayerFallingState(Player* player, Animation* animation)
{
	m_player = player;
	m_animation = animation;
}


PlayerFallingState::~PlayerFallingState()
{
}

void PlayerFallingState::Update(float deltaTime)
{
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);
	m_animation->Update(deltaTime);
}

void PlayerFallingState::Draw()
{
	m_animation->Draw();
}

PlayerStates PlayerFallingState::GetState()
{
	return PlayerStates::Falling;
}

void PlayerFallingState::OnCollision(GameObject* entity, float deltaTime)
{
}
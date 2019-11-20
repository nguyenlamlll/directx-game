#include "stdafx.h"
#include "PlayerJumpMovingState.h"

PlayerJumpMovingState::PlayerJumpMovingState(Player* player, Animation* animation)
{
	m_player = player;
	m_animation = animation;
}


PlayerJumpMovingState::~PlayerJumpMovingState()
{
}

void PlayerJumpMovingState::Update(float deltaTime)
{
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);
	m_animation->Update(deltaTime);
}

void PlayerJumpMovingState::Draw()
{
	m_animation->Draw();
}

PlayerStates PlayerJumpMovingState::GetState()
{
	return PlayerStates::Falling;
}

void PlayerJumpMovingState::OnCollision(GameObject* entity, float deltaTime)
{
}
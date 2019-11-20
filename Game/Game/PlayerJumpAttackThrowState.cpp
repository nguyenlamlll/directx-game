#include "stdafx.h"
#include "PlayerJumpAttackThrowState.h"

PlayerJumpAttackThrowState::PlayerJumpAttackThrowState(Player* player, Animation* animation)
{
	m_player = player;
	m_animation = animation;
}


PlayerJumpAttackThrowState::~PlayerJumpAttackThrowState()
{
}

void PlayerJumpAttackThrowState::Update(float deltaTime)
{
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);
	m_animation->Update(deltaTime);
}

void PlayerJumpAttackThrowState::Draw()
{
	m_animation->Draw();
}

PlayerStates PlayerJumpAttackThrowState::GetState()
{
	return PlayerStates::JumpAttackThrow;
}

void PlayerJumpAttackThrowState::OnCollision(GameObject* entity, float deltaTime)
{
}
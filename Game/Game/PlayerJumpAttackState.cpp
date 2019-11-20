#include "stdafx.h"
#include "PlayerJumpAttackState.h"

PlayerJumpAttackState::PlayerJumpAttackState(Player* player, Animation* animation)
{
	m_player = player;
	m_animation = animation;
}


PlayerJumpAttackState::~PlayerJumpAttackState()
{
}

void PlayerJumpAttackState::Update(float deltaTime)
{
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);
	m_animation->Update(deltaTime);
}

void PlayerJumpAttackState::Draw()
{
	m_animation->Draw();
}

PlayerStates PlayerJumpAttackState::GetState()
{
	return PlayerStates::JumpAttack;
}

void PlayerJumpAttackState::OnCollision(GameObject* entity, float deltaTime)
{
}

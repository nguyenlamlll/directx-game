#include "stdafx.h"
#include "PlayerSwingAttackState.h"

PlayerSwingAttackState::PlayerSwingAttackState(Player* player, Animation* animation)
{
	m_player = player;
	m_animation = animation;
}


PlayerSwingAttackState::~PlayerSwingAttackState()
{
}

void PlayerSwingAttackState::Update(float deltaTime)
{
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);
	m_animation->Update(deltaTime);
}

void PlayerSwingAttackState::Draw()
{
	m_animation->Draw();
}

PlayerStates PlayerSwingAttackState::GetState()
{
	return PlayerStates::SwingAttack;
}

void PlayerSwingAttackState::OnCollision(GameObject* entity, float deltaTime)
{
}
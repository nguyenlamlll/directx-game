#include "stdafx.h"
#include "PlayerStandAttackState.h"

PlayerStandAttackState::PlayerStandAttackState(Player* player, Animation* animation)
{
	m_player = player;
	m_animation = animation;
}


PlayerStandAttackState::~PlayerStandAttackState()
{
}

void PlayerStandAttackState::Update(float deltaTime)
{
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);
	m_animation->Update(deltaTime);
}

void PlayerStandAttackState::Draw()
{
	m_animation->Draw();
}

PlayerStates PlayerStandAttackState::GetState()
{
	return PlayerStates::StandAttack;
}

void PlayerStandAttackState::OnCollision(GameObject* entity, float deltaTime)
{
}

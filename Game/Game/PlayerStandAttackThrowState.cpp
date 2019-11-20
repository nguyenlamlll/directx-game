#include "stdafx.h"
#include "PlayerStandAttackThrowState.h"

PlayerStandAttackThrowState::PlayerStandAttackThrowState(Player* player, Animation* animation)
{
	m_player = player;
	m_animation = animation;
}


PlayerStandAttackThrowState::~PlayerStandAttackThrowState()
{
}

void PlayerStandAttackThrowState::Update(float deltaTime)
{
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);
	m_animation->Update(deltaTime);
}

void PlayerStandAttackThrowState::Draw()
{
	m_animation->Draw();
}

PlayerStates PlayerStandAttackThrowState::GetState()
{
	return PlayerStates::Falling;
}

void PlayerStandAttackThrowState::OnCollision(GameObject* entity, float deltaTime)
{
}
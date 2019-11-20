#include "stdafx.h"
#include "PlayerSitDownAttackThrowState.h"

PlayerSitDownAttackThrowState::PlayerSitDownAttackThrowState(Player* player, Animation* animation)
{
	m_player = player;
	m_animation = animation;
}


PlayerSitDownAttackThrowState::~PlayerSitDownAttackThrowState()
{
}

void PlayerSitDownAttackThrowState::Update(float deltaTime)
{
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);
	m_animation->Update(deltaTime);
}

void PlayerSitDownAttackThrowState::Draw()
{
	m_animation->Draw();
}

PlayerStates PlayerSitDownAttackThrowState::GetState()
{
	return PlayerStates::SitDownAttackThrow;
}

void PlayerSitDownAttackThrowState::OnCollision(GameObject* entity, float deltaTime)
{
}
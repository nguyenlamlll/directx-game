#include "stdafx.h"
#include "PlayerSitDownAttack.h"

PlayerSitDownAttack::PlayerSitDownAttack(Player* player, Animation* animation)
{
	m_player = player;
	m_animation = animation;
}


PlayerSitDownAttack::~PlayerSitDownAttack()
{
}

void PlayerSitDownAttack::Update(float deltaTime)
{
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);
	m_animation->Update(deltaTime);
}

void PlayerSitDownAttack::Draw()
{
	m_animation->Draw();
}

PlayerStates PlayerSitDownAttack::GetState()
{
	return PlayerStates::SitDownAttack;
}

void PlayerSitDownAttack::OnCollision(GameObject* entity, float deltaTime)
{
}

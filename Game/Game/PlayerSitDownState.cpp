#include "stdafx.h"
#include "PlayerSitDownState.h"


PlayerSitDownState::PlayerSitDownState(Player* player, Animation* animation)
{
	m_player = player;
	m_animation = animation;
}


PlayerSitDownState::~PlayerSitDownState()
{
}

void PlayerSitDownState::Update(float deltaTime)
{
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);
	m_animation->Update(deltaTime);
}

void PlayerSitDownState::Draw()
{
	m_animation->Draw();
}

PlayerStates PlayerSitDownState::GetState()
{
	return PlayerStates::SitDown;
}

void PlayerSitDownState::OnCollision(GameObject* entity, float deltaTime)
{
}

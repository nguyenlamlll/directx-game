#include "stdafx.h"
#include "PlayerStandingState.h"


PlayerStandingState::PlayerStandingState(Player* player, Animation* animation)
{
	m_player = player;
	m_animation = animation;
}


PlayerStandingState::~PlayerStandingState()
{
}

void PlayerStandingState::Update(float deltaTime)
{
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);
	m_animation->Update(deltaTime);
}

void PlayerStandingState::Draw()
{
	m_animation->Draw();
}

PlayerStates PlayerStandingState::GetState()
{
	return PlayerStates::Standing;
}

void PlayerStandingState::OnCollision(GameObject * entity, float deltaTime)
{
}

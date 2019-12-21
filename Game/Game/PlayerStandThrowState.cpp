#include "stdafx.h"
#include "PlayerStandThrowState.h"

PlayerStandThrowState::PlayerStandThrowState(Player* player, Animation* animation)
{
	m_player = player;
	m_animation = animation;

}


PlayerStandThrowState::~PlayerStandThrowState()
{
}

void PlayerStandThrowState::Update(float deltaTime)
{
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);
	m_animation->Update(deltaTime);
}

void PlayerStandThrowState::Draw()
{
	m_animation->Draw();
}

PlayerStates PlayerStandThrowState::GetState()
{
	return PlayerStates::StandingThrow;
}

void PlayerStandThrowState::PreCollision(GameObject * entity, float deltaTime)
{
}

void PlayerStandThrowState::OnCollision(GameObject* entity, float deltaTime)
{
}



#include "stdafx.h"
#include "PlayerEndGameState.h"

PlayerEndGameState::PlayerEndGameState(Player* player, Animation* animation)
{
	m_player = player;
	m_animation = animation;
}


PlayerEndGameState::~PlayerEndGameState()
{
}

void PlayerEndGameState::Update(float deltaTime)
{
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);
	m_animation->Update(deltaTime);
}

void PlayerEndGameState::Draw()
{
	m_animation->Draw();
}

PlayerStates PlayerEndGameState::GetState()
{
	return PlayerStates::EndLevel;
}

void PlayerEndGameState::OnCollision(GameObject* entity, float deltaTime)
{
}
#include "stdafx.h"
#include "PlayerLookUpState.h"

PlayerLookUpState::PlayerLookUpState(Player* player, Animation* animation)
{
	m_player = player;
	m_animation = animation;
}


PlayerLookUpState::~PlayerLookUpState()
{
}

void PlayerLookUpState::Update(float deltaTime)
{
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);
	m_animation->Update(deltaTime);
}

void PlayerLookUpState::Draw()
{
	m_animation->Draw();
}

PlayerStates PlayerLookUpState::GetState()
{
	return PlayerStates::LookUp;
}

void PlayerLookUpState::OnCollision(GameObject* entity, float deltaTime)
{
}

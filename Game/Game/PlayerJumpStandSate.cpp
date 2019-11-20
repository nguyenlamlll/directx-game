#include "stdafx.h"
#include "PlayerJumpStandSate.h"

PlayerJumpStandSate::PlayerJumpStandSate(Player* player, Animation* animation)
{
	m_player = player;
	m_animation = animation;
}


PlayerJumpStandSate::~PlayerJumpStandSate()
{
}

void PlayerJumpStandSate::Update(float deltaTime)
{
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);
	m_animation->Update(deltaTime);
}

void PlayerJumpStandSate::Draw()
{
	m_animation->Draw();
}

PlayerStates PlayerJumpStandSate::GetState()
{
	return PlayerStates::JumpStand;
}

void PlayerJumpStandSate::OnCollision(GameObject* entity, float deltaTime)
{
}
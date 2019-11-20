#include "stdafx.h"
#include "PlayerJumpStandSate.h"

PlayerJumpStandSate::PlayerJumpStandSate(Player* player, Animation* animation)
{
	m_player = player;
	m_animation = animation;
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);

	m_initialY = m_player->getPosition().y;

	m_travelledJumpDistance = 0.0f;
	m_longestJumpDistance = 120.0f;
}


PlayerJumpStandSate::~PlayerJumpStandSate()
{
}

void PlayerJumpStandSate::Update(float deltaTime)
{
	float vy = 0.0f;
	if (m_travelledJumpDistance >= m_longestJumpDistance) {
		vy = m_player->speed * deltaTime;

	}
	else {
		vy = -m_player->speed * deltaTime;
	}
	m_travelledJumpDistance += abs(vy);
	m_player->setPosition(D3DXVECTOR2(m_player->getPosition().x, m_player->getPosition().y + vy));
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);
	m_animation->Update(deltaTime);

	if (m_travelledJumpDistance >= m_longestJumpDistance*2) {
		m_player->changeState(PlayerStates::Standing);
		return;
	}
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
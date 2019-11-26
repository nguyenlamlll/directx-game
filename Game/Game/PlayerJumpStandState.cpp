#include "stdafx.h"
#include "PlayerJumpStandState.h"

PlayerJumpStandState::PlayerJumpStandState(Player* player, Animation* animation)
{
	m_player = player;
	m_animation = animation;
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);

	m_initialY = m_player->m_basePosition.y;

	m_travelledJumpDistance = 0.0f;
	m_longestJumpDistance = 120.0f;

	if (m_player->m_isFacingRight == true)
	{
		m_animation->setFlipHorizontal(false);
	}
	if (m_player->m_isFacingRight == false)
	{
		m_animation->setFlipHorizontal(true);
	}
}


PlayerJumpStandState::~PlayerJumpStandState()
{
}

void PlayerJumpStandState::Update(float deltaTime)
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

	// Attack with sword while jumping
	if (KeyboardInput::GetInstance()->isKeyTriggered(VK_J))
	{
		m_player->changeState(PlayerStates::JumpAttack);
		return;
	}
	// Attack by throwing apples while jumping
	if (KeyboardInput::GetInstance()->isKeyTriggered(VK_K))
	{
		m_player->changeState(PlayerStates::JumpAttackThrow);
		return;
	}


	if (m_travelledJumpDistance >= m_longestJumpDistance * 2) {
		m_player->setPosition(D3DXVECTOR2(m_player->getPosition().x, m_initialY));
		if (KeyboardInput::GetInstance()->isKeyDown(VK_D) || KeyboardInput::GetInstance()->isKeyDown(VK_A))
		{
			m_player->changeState(PlayerStates::Moving);
			return;
		}
		m_player->changeState(PlayerStates::Standing);
		return;
	}
}

void PlayerJumpStandState::Draw()
{
	m_animation->Draw();
}

PlayerStates PlayerJumpStandState::GetState()
{
	return PlayerStates::JumpStand;
}

void PlayerJumpStandState::OnCollision(GameObject* entity, float deltaTime)
{
}

float PlayerJumpStandState::getInitialY()
{
	return m_initialY;
}

float PlayerJumpStandState::getTravelledJumpDistance()
{
	return m_travelledJumpDistance;
}

float PlayerJumpStandState::getLongestJumpDistance()
{
	return m_longestJumpDistance;
}

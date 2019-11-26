#include "stdafx.h"
#include "PlayerJumpMovingState.h"

PlayerJumpMovingState::PlayerJumpMovingState(Player* player, Animation* animation)
{
	m_player = player;
	m_animation = animation;
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);

	m_initialY = m_player->getPosition().y;

	m_travelledJumpDistance = 0.0f;
	m_longestJumpDistance = 120.0f;
}


PlayerJumpMovingState::~PlayerJumpMovingState()
{
}

void PlayerJumpMovingState::Update(float deltaTime)
{
	if (KeyboardInput::GetInstance()->isKeyDown(VK_A))
	{
		m_animation->setFlipHorizontal(true);
	}
	if (KeyboardInput::GetInstance()->isKeyDown(VK_D))
	{
		m_animation->setFlipHorizontal(false);
	}

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

void PlayerJumpMovingState::Draw()
{
	m_animation->Draw();
}

PlayerStates PlayerJumpMovingState::GetState()
{
	return PlayerStates::JumpMoving;
}

void PlayerJumpMovingState::OnCollision(GameObject* entity, float deltaTime)
{
}

float PlayerJumpMovingState::getInitialY()
{
	return m_initialY;
}

float PlayerJumpMovingState::getTravelledJumpDistance()
{
	return m_travelledJumpDistance;
}

float PlayerJumpMovingState::getLongestJumpDistance()
{
	return m_longestJumpDistance;
}

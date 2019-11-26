#include "stdafx.h"
#include "PlayerSitDownState.h"


PlayerSitDownState::PlayerSitDownState(Player* player, Animation* animation)
{
	m_player = player;
	m_animation = animation;
	m_animation->Reset();
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);

	if (m_player->m_isFacingRight == false)
	{
		m_animation->setFlipHorizontal(true);
	}
	else {
		m_animation->setFlipHorizontal(false);
	}
}


PlayerSitDownState::~PlayerSitDownState()
{
}

void PlayerSitDownState::Update(float deltaTime)
{
	// From Sit Down back to Standing
	if (KeyboardInput::GetInstance()->isKeyReleased(VK_S))
	{
		m_player->changeState(PlayerStates::Standing);
		return;
	}

	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);
	m_animation->Update(deltaTime);

	// From Sit to Sit Attack
	if (KeyboardInput::GetInstance()->isKeyReleased(VK_J))
	{
		m_player->changeState(PlayerStates::SitDownAttack);
		return;
	}

	// From Sit to Sit Attack Throw
	if (KeyboardInput::GetInstance()->isKeyReleased(VK_K))
	{
		m_player->changeState(PlayerStates::SitDownAttackThrow);
		return;
	}
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

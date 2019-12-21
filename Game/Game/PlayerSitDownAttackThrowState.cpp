#include "stdafx.h"
#include "PlayerSitDownAttackThrowState.h"

PlayerSitDownAttackThrowState::PlayerSitDownAttackThrowState(Player* player, Animation* animation)
{
	m_player = player;
	m_animation = animation;
	m_animation->Reset();
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);

	if (m_player->getIsFacingRight() == false)
	{
		m_animation->setFlipHorizontal(true);
	}
	else {
		m_animation->setFlipHorizontal(false);
	}
}


PlayerSitDownAttackThrowState::~PlayerSitDownAttackThrowState()
{
}

void PlayerSitDownAttackThrowState::Update(float deltaTime)
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

	if (m_animation->getIsFinished() == true)
	{
		m_player->changeState(PlayerStates::SitDown);
		dynamic_cast<PlayerSitDownState*>(m_player->getCurrentState())->setIsFixedSittingDown(true);
		return;
	}
}

void PlayerSitDownAttackThrowState::Draw()
{
	m_animation->Draw();
}

PlayerStates PlayerSitDownAttackThrowState::GetState()
{
	return PlayerStates::SitDownAttackThrow;
}

void PlayerSitDownAttackThrowState::PreCollision(GameObject * entity, float deltaTime)
{
}

void PlayerSitDownAttackThrowState::OnCollision(GameObject* entity, float deltaTime)
{
}
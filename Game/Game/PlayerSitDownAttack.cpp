#include "stdafx.h"
#include "PlayerSitDownAttack.h"

PlayerSitDownAttack::PlayerSitDownAttack(Player* player, Animation* animation)
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


PlayerSitDownAttack::~PlayerSitDownAttack()
{
}

void PlayerSitDownAttack::Update(float deltaTime)
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
		return;
	}
}

void PlayerSitDownAttack::Draw()
{
	m_animation->Draw();
}

PlayerStates PlayerSitDownAttack::GetState()
{
	return PlayerStates::SitDownAttack;
}

void PlayerSitDownAttack::OnCollision(GameObject* entity, float deltaTime)
{
}

#include "stdafx.h"
#include "PlayerStandAttackState.h"

PlayerStandAttackState::PlayerStandAttackState(Player* player, Animation* animation)
{
	m_player = player;
	m_animation = animation;
	m_animation->Reset();
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);
	if (m_player->m_isFacingRight == true)
	{
		m_animation->setFlipHorizontal(false);
	}
	if (m_player->m_isFacingRight == false)
	{
		m_animation->setFlipHorizontal(true);
	}
}


PlayerStandAttackState::~PlayerStandAttackState()
{
}

void PlayerStandAttackState::Update(float deltaTime)
{
	if (KeyboardInput::GetInstance()->isKeyDown(VK_A)) {
		m_animation->setFlipHorizontal(true);
	}
	if (KeyboardInput::GetInstance()->isKeyDown(VK_D)) {
		m_animation->setFlipHorizontal(false);
	}

	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);
	m_animation->Update(deltaTime);

	if (m_animation->getIsFinished() == true) 
	{
		m_player->changeState(PlayerStates::Standing);
		return;
	}
}

void PlayerStandAttackState::Draw()
{
	m_animation->Draw();
}

PlayerStates PlayerStandAttackState::GetState()
{
	return PlayerStates::StandAttack;
}

void PlayerStandAttackState::OnCollision(GameObject* entity, float deltaTime)
{
}

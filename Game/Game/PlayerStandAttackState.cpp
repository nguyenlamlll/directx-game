#include "stdafx.h"
#include "PlayerStandAttackState.h"

constexpr auto sprite_offset = 12;

PlayerStandAttackState::PlayerStandAttackState(Player* player, Animation* animation)
{
	m_player = player;
	m_animation = animation;
	m_animation->Reset();
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y - sprite_offset);
	if (m_player->getIsFacingRight() == true)
	{
		m_animation->setFlipHorizontal(false);
	}
	if (m_player->getIsFacingRight() == false)
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
	m_animation->setPositionY(m_player->getPosition().y - sprite_offset);
	m_animation->Update(deltaTime);

	if (m_animation->getIsFinished() == true) 
	{
		if (KeyboardInput::GetInstance()->isKeyDown(VK_A) || KeyboardInput::GetInstance()->isKeyDown(VK_D)) {
			m_player->changeState(PlayerStates::Moving);
			return;
		}
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

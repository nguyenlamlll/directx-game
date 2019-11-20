#include "stdafx.h"
#include "PlayerStandingState.h"


PlayerStandingState::PlayerStandingState(Player* player, Animation* animation)
{
	m_player = player;
	m_animation = animation;
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);
}


PlayerStandingState::~PlayerStandingState()
{
}

void PlayerStandingState::Update(float deltaTime)
{
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);
	m_animation->Update(deltaTime);

	if (KeyboardInput::GetInstance()->isKeyTriggered(VK_D) || KeyboardInput::GetInstance()->isKeyTriggered(VK_A))
	{
		m_player->changeState(PlayerStates::Moving);
		return;
	}
	if (KeyboardInput::GetInstance()->isKeyTriggered(VK_SPACE))
	{
		m_player->changeState(PlayerStates::JumpStand);
		return;
	}
	if (KeyboardInput::GetInstance()->isKeyTriggered(VK_W))
	{
		m_player->changeState(PlayerStates::LookUp);
		return;
	}
}

void PlayerStandingState::Draw()
{
	m_animation->Draw();
}

PlayerStates PlayerStandingState::GetState()
{
	return PlayerStates::Standing;
}

void PlayerStandingState::OnCollision(GameObject * entity, float deltaTime)
{
}

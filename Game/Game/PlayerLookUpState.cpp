#include "stdafx.h"
#include "PlayerLookUpState.h"

PlayerLookUpState::PlayerLookUpState(Player* player, Animation* animation)
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


PlayerLookUpState::~PlayerLookUpState()
{
}

void PlayerLookUpState::Update(float deltaTime)
{
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);
	m_animation->Update(deltaTime);

	if (KeyboardInput::GetInstance()->isKeyReleased(VK_W))
	{
		m_player->changeState(PlayerStates::Standing);
		return;
	}
}

void PlayerLookUpState::Draw()
{
	m_animation->Draw();
}

PlayerStates PlayerLookUpState::GetState()
{
	return PlayerStates::LookUp;
}

void PlayerLookUpState::OnCollision(GameObject* entity, float deltaTime)
{
}

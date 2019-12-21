#include "stdafx.h"
#include "PlayerStandAttackThrowState.h"

PlayerStandAttackThrowState::PlayerStandAttackThrowState(Player* player, Animation* animation)
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

	Sound::getInstance()->play(SoundNames::THROW_APPLE_SOUND, false, 1);
}


PlayerStandAttackThrowState::~PlayerStandAttackThrowState()
{
}

void PlayerStandAttackThrowState::Update(float deltaTime)
{
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);
	m_animation->Update(deltaTime);

	if (m_animation->getIsFinished() == true)
	{
		if (KeyboardInput::GetInstance()->isKeyDown(VK_D) || KeyboardInput::GetInstance()->isKeyDown(VK_A))
		{
			m_player->changeState(PlayerStates::Moving);
			return;
		}
		m_player->changeState(PlayerStates::Standing);
		return;
	}
}

void PlayerStandAttackThrowState::Draw()
{
	m_animation->Draw();
}

PlayerStates PlayerStandAttackThrowState::GetState()
{
	return PlayerStates::Falling;
}

void PlayerStandAttackThrowState::PreCollision(GameObject * entity, float deltaTime)
{
}

void PlayerStandAttackThrowState::OnCollision(GameObject* entity, float deltaTime)
{
}
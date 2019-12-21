#include "stdafx.h"
#include "PlayerMoveThrowState.h"

#define SPRITE_OFFSET 10

PlayerMoveThrowState::PlayerMoveThrowState(Player* player, Animation* animation)
{
	m_player = player;
	m_animation = animation;
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y - SPRITE_OFFSET);
	m_animation->Reset();

	if (m_player->getIsFacingRight() == true)
	{
		m_animation->setFlipHorizontal(false);
	}
	else
	{
		m_animation->setFlipHorizontal(true);
	}

	Sound::getInstance()->play(SoundNames::THROW_APPLE_SOUND, false, 1);
}


PlayerMoveThrowState::~PlayerMoveThrowState()
{
}

void PlayerMoveThrowState::Update(float deltaTime)
{
	if (KeyboardInput::GetInstance()->isKeyDown(VK_A)) {
		m_animation->setFlipHorizontal(true);
	}
	if (KeyboardInput::GetInstance()->isKeyDown(VK_D)) {
		m_animation->setFlipHorizontal(false);
	}

	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y - SPRITE_OFFSET);
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

void PlayerMoveThrowState::Draw()
{
	m_animation->Draw();
}

PlayerStates PlayerMoveThrowState::GetState()
{
	return PlayerStates::MoveThrow;
}

void PlayerMoveThrowState::PreCollision(GameObject * entity, float deltaTime)
{
}

void PlayerMoveThrowState::OnCollision(GameObject * entity, float deltaTime)
{
}

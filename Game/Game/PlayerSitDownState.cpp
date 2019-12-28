#include "stdafx.h"
#include "PlayerSitDownState.h"


PlayerSitDownState::PlayerSitDownState(Player* player, Animation* animation, bool isFixedSatDown)
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

	setIsFixedSittingDown(isFixedSatDown);
}


PlayerSitDownState::~PlayerSitDownState()
{
}

void PlayerSitDownState::Update(float deltaTime)
{
	// From Sit Down back to Standing
	if (KeyboardInput::GetInstance()->isKeyReleased(PlayerInputs::SIT_DOWN))
	{
		m_player->changeState(PlayerStates::Standing);
		return;
	}

	if (KeyboardInput::GetInstance()->isKeyDown(PlayerInputs::MOVE_LEFT)) {
		m_animation->setFlipHorizontal(true);
	}
	if (KeyboardInput::GetInstance()->isKeyDown(PlayerInputs::MOVE_RIGHT)) {
		m_animation->setFlipHorizontal(false);
	}


	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);
	if (!m_isFixedSatDown)
	{
		m_animation->Update(deltaTime);
	}

	// From Sit to Sit Attack
	if (KeyboardInput::GetInstance()->isKeyReleased(PlayerInputs::ATTACK))
	{
		m_player->changeState(PlayerStates::SitDownAttack);
		return;
	}

	// From Sit to Sit Attack Throw
	if (KeyboardInput::GetInstance()->isKeyReleased(PlayerInputs::THROW_APPLE))
	{
		if (m_player->m_appleCount > 0)
		{
			m_player->changeState(PlayerStates::SitDownAttackThrow);
		}
		else
		{
			Sound::getInstance()->play(SoundNames::OUTTA_APPLE_SOUND, false);
		}
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

void PlayerSitDownState::PreCollision(GameObject * entity, float deltaTime)
{
}

void PlayerSitDownState::OnCollision(GameObject* entity, float deltaTime)
{
}

void PlayerSitDownState::setIsFixedSittingDown(bool value)
{
	m_isFixedSatDown = value;
	if (m_isFixedSatDown)
	{
		m_animation->setIndexFrame(3);
	}
}

bool PlayerSitDownState::isSatDown()
{
	return m_isFixedSatDown;
}

#include "stdafx.h"
#include "PlayerClimbThrowState.h"


PlayerClimbThrowState::PlayerClimbThrowState(Player* player, Animation* animation)
{
	m_player = player;
	m_animation = animation;
	m_animation->Reset();
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);
	if (m_player->getIsFacingRight() == true)
	{
		m_animation->setFlipHorizontal(false);
	}
	if (m_player->getIsFacingRight() == false)
	{
		m_animation->setFlipHorizontal(true);
	}
}


PlayerClimbThrowState::~PlayerClimbThrowState()
{
}

void PlayerClimbThrowState::attachClimbArea(ClimbArea * area)
{
	m_climbArea = area;
}

void PlayerClimbThrowState::Update(float deltaTime)
{
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);
	m_animation->Update(deltaTime);

	if (m_animation->getIndexFrame() == 4 && m_isAppleThrowed == false)
	{
		Sound::getInstance()->play(SoundNames::THROW_APPLE_SOUND, false, 1);
		createAppleBullet();
		m_isAppleThrowed = true;
	}

	if (m_animation->getIsFinished() == true)
	{
		if (KeyboardInput::GetInstance()->isKeyDown(PlayerInputs::MOVE_LEFT) ||
			KeyboardInput::GetInstance()->isKeyDown(PlayerInputs::MOVE_RIGHT))
		{
			m_player->changeState(PlayerStates::Moving);
			return;
		}
		m_player->changeState(PlayerStates::Climb);
		auto climbState = dynamic_cast<PlayerClimbState*>(m_player->getCurrentState());
		climbState->attachClimbArea(m_climbArea);
		return;
	}
}

void PlayerClimbThrowState::Draw()
{
	m_animation->Draw();
}

PlayerStates PlayerClimbThrowState::GetState()
{
	return PlayerStates::ClimbThrow;
}

void PlayerClimbThrowState::PreCollision(GameObject * entity, float deltaTime)
{
}

void PlayerClimbThrowState::OnCollision(GameObject * entity, float deltaTime)
{
}

void PlayerClimbThrowState::createAppleBullet()
{
	int appleX, appleY;
	if (m_player->getIsFacingRight())
		appleX = m_animation->getPositionX() + 10;
	else
		appleX = m_animation->getPositionX() - 10;
	appleY = m_animation->getPositionY() - 30;
	AppleBullet* apple = new AppleBullet(appleX, appleY, 0, 0, m_player->getIsFacingRight());
	m_player->addAppleToList(apple);
}

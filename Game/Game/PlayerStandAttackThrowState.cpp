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
}


PlayerStandAttackThrowState::~PlayerStandAttackThrowState()
{
}

void PlayerStandAttackThrowState::Update(float deltaTime)
{
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);
	m_animation->Update(deltaTime);

	if (m_animation->getIndexFrame() == 3 && m_animation->getcurTotalTime() > 60.f)
	{
		Sound::getInstance()->play(SoundNames::THROW_APPLE_SOUND, false, 1);
		createAppleBullet();
	}

	if (m_animation->getIsFinished() == true)
	{
		if (KeyboardInput::GetInstance()->isKeyDown(PlayerInputs::MOVE_RIGHT) || KeyboardInput::GetInstance()->isKeyDown(PlayerInputs::MOVE_LEFT))
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
	return PlayerStates::StandAttackThrow;
}

void PlayerStandAttackThrowState::PreCollision(GameObject * entity, float deltaTime)
{
}

void PlayerStandAttackThrowState::OnCollision(GameObject* entity, float deltaTime)
{
}

void PlayerStandAttackThrowState::createAppleBullet() {
	int appleX, appleY;
	if (m_player->getIsFacingRight())
		appleX = m_animation->getPositionX() + 10;
	else
		appleX = m_animation->getPositionX() - 10;
	appleY = m_animation->getPositionY() - 30;
	AppleBullet* apple = new AppleBullet(appleX, appleY, 0, 0, m_player->getIsFacingRight());
	m_player->addAppleToList(apple);
}


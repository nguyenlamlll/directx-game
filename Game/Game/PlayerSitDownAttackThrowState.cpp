#include "stdafx.h"
#include "PlayerSitDownAttackThrowState.h"

PlayerSitDownAttackThrowState::PlayerSitDownAttackThrowState(Player* player, Animation* animation)
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


PlayerSitDownAttackThrowState::~PlayerSitDownAttackThrowState()
{
}

void PlayerSitDownAttackThrowState::Update(float deltaTime)
{
	// From Sit Down back to Standing
	if (KeyboardInput::GetInstance()->isKeyReleased(PlayerInputs::SIT_DOWN))
	{
		m_player->changeState(PlayerStates::Standing);
		return;
	}

	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);
	m_animation->Update(deltaTime);
	if (m_animation->getIndexFrame() == 3 && m_animation->getcurTotalTime()> 60.f)
		createAppleBullet();

	if (m_animation->getIsFinished() == true)
	{
		m_player->changeState(PlayerStates::SitDown);
		dynamic_cast<PlayerSitDownState*>(m_player->getCurrentState())->setIsFixedSittingDown(true);
		return;
	}
}

void PlayerSitDownAttackThrowState::Draw()
{
	m_animation->Draw();
}

PlayerStates PlayerSitDownAttackThrowState::GetState()
{
	return PlayerStates::SitDownAttackThrow;
}

void PlayerSitDownAttackThrowState::PreCollision(GameObject * entity, float deltaTime)
{
}

void PlayerSitDownAttackThrowState::OnCollision(GameObject* entity, float deltaTime)
{
}


void PlayerSitDownAttackThrowState::createAppleBullet() {
	int appleX, appleY;
	if (m_player->getIsFacingRight())
		appleX = m_animation->getPositionX() + 10;
	else
		appleX = m_animation->getPositionX() - 10;
	appleY = m_animation->getPositionY();
	AppleBullet* apple = new AppleBullet(appleX, appleY, 0, 0, m_player->getIsFacingRight());
	m_player->addAppleToList(apple);
}

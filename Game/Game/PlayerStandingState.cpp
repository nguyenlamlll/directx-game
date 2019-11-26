#include "stdafx.h"
#include "PlayerStandingState.h"

#define IDLE_TIME 1500

PlayerStandingState::PlayerStandingState(Player* player, Animation* animation)
{
	m_player = player;
	m_animationStand = animation;
	m_animation = animation;
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);

	m_animationStandLookAround = DBG_NEW Animation(L"Resources/animations/aladdin/stand-look-around.png", 7, 1, 7, true, 150.f);

	if (m_player->m_isFacingRight == false)
	{
		m_animation->setFlipHorizontal(true);
	}
	else {
		m_animation->setFlipHorizontal(false);
	}
}


PlayerStandingState::~PlayerStandingState()
{
	if (m_animationStandLookAround != nullptr)
	{
		delete m_animationStandLookAround;
	}
}

void PlayerStandingState::Update(float deltaTime)
{
	if (m_idleTime >= IDLE_TIME)
	{
		m_animationStandLookAround->Reset();
		m_animation = m_animationStandLookAround;
		if (m_player->m_isFacingRight == false)
		{
			m_animation->setFlipHorizontal(true);
		}
		else {
			m_animation->setFlipHorizontal(false);
		}
		m_idleTime = 0;
	}
	else 
	{
		m_idleTime += deltaTime;
	}

	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);
	m_animation->Update(deltaTime);

	// Prevent moving when pressing both A and D keys.
	if (KeyboardInput::GetInstance()->isKeyDown(VK_A) && KeyboardInput::GetInstance()->isKeyDown(VK_D))
	{
		return;
	}

	// From Stand to Moving state.
	if (KeyboardInput::GetInstance()->isKeyTriggered(VK_D) || KeyboardInput::GetInstance()->isKeyTriggered(VK_A))
	{
		m_player->changeState(PlayerStates::Moving);
		return;
	}

	// From Stand to Sit
	if (KeyboardInput::GetInstance()->isKeyTriggered(VK_S))
	{
		m_player->changeState(PlayerStates::SitDown);
		return;
	}

	// From Stand to JumpStand (jump while standing).
	if (KeyboardInput::GetInstance()->isKeyTriggered(VK_SPACE))
	{
		m_player->changeState(PlayerStates::JumpStand);
		return;
	}

	// From Stand to Look Up.
	if (KeyboardInput::GetInstance()->isKeyTriggered(VK_W))
	{
		m_player->changeState(PlayerStates::LookUp);
		return;
	}

	// From Stand to Attack (swinging the sword).
	if (KeyboardInput::GetInstance()->isKeyTriggered(VK_J))
	{
		m_player->changeState(PlayerStates::StandAttack);
		return;
	}
	// From Stand to Attack by Throwing apples
	if (KeyboardInput::GetInstance()->isKeyTriggered(VK_K))
	{
		m_player->changeState(PlayerStates::StandAttackThrow);
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

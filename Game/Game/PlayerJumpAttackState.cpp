#include "stdafx.h"
#include "PlayerJumpAttackState.h"

PlayerJumpAttackState::PlayerJumpAttackState(Player* player, Animation* animation)
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

	switch (m_player->getPreviousState()->GetState()) {
	case (PlayerStates::JumpMoving):
	{
		m_initialY = dynamic_cast<PlayerJumpMovingState*>(m_player->getPreviousState())->getInitialY();
		m_travelledJumpDistance = dynamic_cast<PlayerJumpMovingState*>(m_player->getPreviousState())->getTravelledJumpDistance();
		m_longestJumpDistance = dynamic_cast<PlayerJumpMovingState*>(m_player->getPreviousState())->getLongestJumpDistance();
		break;
	}
	case (PlayerStates::JumpStand):
	{
		m_initialY = dynamic_cast<PlayerJumpStandState*>(m_player->getPreviousState())->getInitialY();
		m_travelledJumpDistance = dynamic_cast<PlayerJumpStandState*>(m_player->getPreviousState())->getTravelledJumpDistance();
		m_longestJumpDistance = dynamic_cast<PlayerJumpStandState*>(m_player->getPreviousState())->getLongestJumpDistance();
		break;
	}
	}
}


PlayerJumpAttackState::~PlayerJumpAttackState()
{
}

void PlayerJumpAttackState::Update(float deltaTime)
{
	float vy = 0.0f;
	if (m_travelledJumpDistance >= m_longestJumpDistance) {
		vy = m_player->speed * deltaTime;

	}
	else {
		vy = -m_player->speed * deltaTime;
	}
	m_travelledJumpDistance += abs(vy);
	m_player->setPosition(D3DXVECTOR2(m_player->getPosition().x, m_player->getPosition().y + vy));

	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);
	m_animation->Update(deltaTime);

	if (m_travelledJumpDistance >= m_longestJumpDistance * 2) {
		m_player->setPosition(D3DXVECTOR2(m_player->getPosition().x, m_initialY));
		if (KeyboardInput::GetInstance()->isKeyDown(VK_D) || KeyboardInput::GetInstance()->isKeyDown(VK_A))
		{
			m_player->changeState(PlayerStates::Moving);
			return;
		}
		m_player->changeState(PlayerStates::Standing);
		return;
	}
	//else if (m_animation->getIsFinished() == true)
	//{
	//	m_player->changeState(PlayerStates::Falling);
	//	return;
	//}
}

void PlayerJumpAttackState::Draw()
{
	m_animation->Draw();
}

PlayerStates PlayerJumpAttackState::GetState()
{
	return PlayerStates::JumpAttack;
}

void PlayerJumpAttackState::OnCollision(GameObject* entity, float deltaTime)
{
}

#include "stdafx.h"
#include "PlayerClimbState.h"

PlayerClimbState::PlayerClimbState(Player* player, Animation* animation)
{
	m_player = player;
	m_animation = animation;
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);

	if (m_player->getIsFacingRight() == false)
	{
		m_animation->setFlipHorizontal(true);
	}
	else
	{
		m_animation->setFlipHorizontal(false);
	}
}


PlayerClimbState::~PlayerClimbState()
{
}

void PlayerClimbState::attachClimbArea(ClimbArea * climbArea)
{
	m_climbingArea = climbArea;
}

void PlayerClimbState::Update(float deltaTime)
{
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);
	if (KeyboardInput::GetInstance()->isKeyDown(PlayerInputs::LOOK_UP) || KeyboardInput::GetInstance()->isKeyDown(PlayerInputs::SIT_DOWN))
	{
		m_animation->Update(deltaTime);
	}

	if (KeyboardInput::GetInstance()->isKeyTriggered(PlayerInputs::JUMP))
	{
		m_player->changeState(PlayerStates::ClimbJump);
		auto climbState = dynamic_cast<PlayerClimbJumpState*>(m_player->getCurrentState());
		climbState->attachClimbArea(m_climbingArea);
		return;
	}

	if (KeyboardInput::GetInstance()->isKeyTriggered(PlayerInputs::ATTACK))
	{
		m_player->changeState(PlayerStates::ClimbAttack);
		auto climbState = dynamic_cast<PlayerClimbAttackState*>(m_player->getCurrentState());
		climbState->attachClimbArea(m_climbingArea);
		return;
	}
	if (KeyboardInput::GetInstance()->isKeyTriggered(PlayerInputs::THROW_APPLE))
	{
		m_player->changeState(PlayerStates::ClimbThrow);
		auto climbState = dynamic_cast<PlayerClimbThrowState*>(m_player->getCurrentState());
		climbState->attachClimbArea(m_climbingArea);
		return;
	}

	if (m_player->m_canClimb == false)
	{
		m_player->changeState(PlayerStates::Standing);
		return;
	}
}

void PlayerClimbState::Draw()
{
	m_animation->Draw();
}

PlayerStates PlayerClimbState::GetState()
{
	return PlayerStates::Climb;
}

void PlayerClimbState::PreCollision(GameObject * entity, float deltaTime)
{

}

void PlayerClimbState::OnCollision(GameObject* entity, float deltaTime)
{
	if (entity->getTag() == Tag::ClimbAreaTag)
	{
		if (entity == m_climbingArea)
		{
			auto climbingArea = dynamic_cast<ClimbArea*>(entity);
			Box playerBox = m_player->GetBoundingBox();
			if (!Collision::getInstance()->isColliding(playerBox, climbingArea->GetBoundingBox()))
			{
				OutputDebugString(L"Not hitting climb area any longer.");
				m_player->m_canClimb = false;
			}
		}
	}
}


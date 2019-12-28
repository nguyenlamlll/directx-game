#include "stdafx.h"
#include "PlayerClimbJumpState.h"


bool PlayerClimbJumpState::isFalling()
{
	return m_travelledJumpDistance >= m_longestJumpDistance;
}

PlayerClimbJumpState::PlayerClimbJumpState(Player* player, Animation* animation)
{
	m_player = player;
	m_animation = animation;
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);

	m_initialY = m_player->getPosition().y;

	m_travelledJumpDistance = 0.0f;
	m_longestJumpDistance = 50.0f;

	m_initialCameraY = Camera::getInstance()->getPosition().y;

	if (m_player->getIsFacingRight() == true)
	{
		m_animation->setFlipHorizontal(false);
	}
	if (m_player->getIsFacingRight() == false)
	{
		m_animation->setFlipHorizontal(true);
	}
}


PlayerClimbJumpState::~PlayerClimbJumpState()
{
}

void PlayerClimbJumpState::attachClimbArea(ClimbArea * climbArea)
{
	m_climbingArea = climbArea;
}

void PlayerClimbJumpState::Update(float deltaTime)
{
	if (KeyboardInput::GetInstance()->isKeyDown(VK_A))
	{
		m_animation->setFlipHorizontal(true);
	}
	if (KeyboardInput::GetInstance()->isKeyDown(VK_D))
	{
		m_animation->setFlipHorizontal(false);
	}

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

	auto cameraOldPosition = Camera::getInstance()->getPosition();
	cameraOldPosition.y += vy;
	Camera::getInstance()->setPosition(cameraOldPosition);

}

void PlayerClimbJumpState::Draw()
{
	m_animation->Draw();
}

PlayerStates PlayerClimbJumpState::GetState()
{
	return PlayerStates::ClimbJump;
}

void PlayerClimbJumpState::PreCollision(GameObject * entity, float deltaTime)
{
}

void PlayerClimbJumpState::OnCollision(GameObject * entity, float deltaTime)
{
	if (entity->getTag() == Tag::BrickTag)
	{
		auto brick = dynamic_cast<FloatingBrick*>(entity);
		if (Collision::getInstance()->isColliding(m_player->GetBoundingBox(), brick->GetBoundingBox()))
		{
			if (brick->getStatus() == Status::Allow)
			{
				OutputDebugString(L"[INFO] Player should stand on this brick. \n");

				if (isFalling() && m_player->getPosition().y <= brick->getPosition().y)
				{
					m_player->setPosition(D3DXVECTOR2(m_player->getPosition().x, brick->getPosition().y - (brick->getHeight() + 5)));
					m_player->changeState(PlayerStates::Standing);
					return;
				}
			}
		}
	}

	if (entity->getTag() == Tag::GroundTag)
	{
		auto ground = dynamic_cast<Ground*>(entity);
		auto cameraOldPosition = Camera::getInstance()->getPosition();
		if (Collision::getInstance()->isColliding(m_player->GetBoundingBox(), ground->GetBoundingBox()))
		{

			if (isFalling() && m_player->getPosition().y <= ground->getPosition().y)
			{
				m_player->setPosition(D3DXVECTOR2(m_player->getPosition().x, ground->getPosition().y - 43.f));
				if (KeyboardInput::GetInstance()->isKeyDown(VK_D) || KeyboardInput::GetInstance()->isKeyDown(VK_A))
				{

					cameraOldPosition.y = m_player->getPosition().y - 118;
					Camera::getInstance()->setPosition(cameraOldPosition);
					m_player->changeState(PlayerStates::Moving);
					return;
				}
				cameraOldPosition.y = m_player->getPosition().y - 118;
				Camera::getInstance()->setPosition(cameraOldPosition);
				m_player->changeState(PlayerStates::Standing);
				return;
			}


		}
	}
}

float PlayerClimbJumpState::getInitialY()
{
	return 0.0f;
}

void PlayerClimbJumpState::setTravelledJumpDistance(float value)
{
}

float PlayerClimbJumpState::getTravelledJumpDistance()
{
	return 0.0f;
}

float PlayerClimbJumpState::getLongestJumpDistance()
{
	return 0.0f;
}

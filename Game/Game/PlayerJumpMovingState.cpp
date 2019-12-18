#include "stdafx.h"
#include "PlayerJumpMovingState.h"

bool PlayerJumpMovingState::isFalling()
{
	return m_travelledJumpDistance >= m_longestJumpDistance;
}

PlayerJumpMovingState::PlayerJumpMovingState(Player* player, Animation* animation)
{
	m_player = player;
	m_animation = animation;
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);

	m_initialY = m_player->getPosition().y;

	m_travelledJumpDistance = 0.0f;
	m_longestJumpDistance = 120.0f;

	m_initialCameraY = Camera::getInstance()->getPosition().y;
}


PlayerJumpMovingState::~PlayerJumpMovingState()
{
}

void PlayerJumpMovingState::Update(float deltaTime)
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

	auto cameraOldPosition = Camera::getInstance()->getPosition();
	cameraOldPosition.y += vy * 0.5;
	Camera::getInstance()->setPosition(cameraOldPosition);

	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);
	m_animation->Update(deltaTime);

	// Attack with sword while jumping
	if (KeyboardInput::GetInstance()->isKeyTriggered(VK_J))
	{
		m_player->changeState(PlayerStates::JumpAttack);
		return;
	}
	// Attack by throwing apples while jumping
	if (KeyboardInput::GetInstance()->isKeyTriggered(VK_K))
	{
		m_player->changeState(PlayerStates::JumpAttackThrow);
		return;
	}

	//if (m_travelledJumpDistance >= m_longestJumpDistance * 2) {
	//	m_player->setPosition(D3DXVECTOR2(m_player->getPosition().x, m_initialY));
	//	if (KeyboardInput::GetInstance()->isKeyDown(VK_D) || KeyboardInput::GetInstance()->isKeyDown(VK_A))
	//	{
	//		cameraOldPosition.y = m_initialCameraY;
	//		Camera::getInstance()->setPosition(cameraOldPosition);
	//		m_player->changeState(PlayerStates::Moving);
	//		return;
	//	}
	//	cameraOldPosition.y = m_initialCameraY;
	//	Camera::getInstance()->setPosition(cameraOldPosition);
	//	m_player->changeState(PlayerStates::Standing);
	//	return;
	//}
}

void PlayerJumpMovingState::Draw()
{
	m_animation->Draw();
}

PlayerStates PlayerJumpMovingState::GetState()
{
	return PlayerStates::JumpMoving;
}

void PlayerJumpMovingState::PreCollision(GameObject * entity, float deltaTime)
{
}

void PlayerJumpMovingState::OnCollision(GameObject* entity, float deltaTime)
{
	if (entity->getTag() == Tag::BrickTag)
	{
		auto brick = dynamic_cast<FloatingBrick*>(entity);
		if (Collision::getInstance()->isColliding(m_player->GetBoundingBox(), brick->GetBoundingBox()))
		{
			if (brick->getStatus() == Status::Allow)
			{
				OutputDebugString(L"[INFO] Player (JUMP MOVING) should stand on this brick. \n");

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

float PlayerJumpMovingState::getInitialY()
{
	return m_initialY;
}

float PlayerJumpMovingState::getTravelledJumpDistance()
{
	return m_travelledJumpDistance;
}

float PlayerJumpMovingState::getLongestJumpDistance()
{
	return m_longestJumpDistance;
}

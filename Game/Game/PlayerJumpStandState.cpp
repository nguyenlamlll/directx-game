#include "stdafx.h"
#include "PlayerJumpStandState.h"

PlayerJumpStandState::PlayerJumpStandState(Player* player, Animation* animation)
{
	m_player = player;
	m_animation = animation;
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);

	m_initialY = m_player->getPosition().y;

	m_travelledJumpDistance = 0.0f;
	m_longestJumpDistance = 60.0f;

	if (m_player->getIsFacingRight() == true)
	{
		m_animation->setFlipHorizontal(false);
	}
	if (m_player->getIsFacingRight() == false)
	{
		m_animation->setFlipHorizontal(true);
	}

	m_initialCameraY = Camera::getInstance()->getPosition().y;
}


PlayerJumpStandState::~PlayerJumpStandState()
{
}

void PlayerJumpStandState::Update(float deltaTime)
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

	auto cameraOldPosition = Camera::getInstance()->getPosition();
	cameraOldPosition.y += vy;
	Camera::getInstance()->setPosition(cameraOldPosition);

	if (KeyboardInput::GetInstance()->isKeyTriggered(PlayerInputs::LOOK_UP) || 
		KeyboardInput::GetInstance()->isKeyTriggered(PlayerInputs::SIT_DOWN))
	{
		if (m_player->m_canClimb)
		{
			m_player->changeState(PlayerStates::Climb);
			auto climbState = dynamic_cast<PlayerClimbState*>(m_player->getCurrentState());
			climbState->attachClimbArea(m_climbArea);
			return;
		}
	}

	// Attack with sword while jumping
	if (KeyboardInput::GetInstance()->isKeyTriggered(VK_J))
	{
		m_player->changeState(PlayerStates::JumpAttack);
		return;
	}
	// Attack by throwing apples while jumping
	if (KeyboardInput::GetInstance()->isKeyTriggered(VK_K))
	{
		if (m_player->m_appleCount > 0)
		{
			m_player->changeState(PlayerStates::JumpAttackThrow);
		}
		else
		{
			Sound::getInstance()->play(SoundNames::OUTTA_APPLE_SOUND, false);
		}
		return;
	}


	//if (m_travelledJumpDistance >= m_longestJumpDistance * 2) 
	//if (m_player->getPosition().y >= 1580.f)
	//{
	//	m_player->setPosition(D3DXVECTOR2(m_player->getPosition().x, 1580.f)); // 1580.f is the bottom ground of PlayScene.
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

void PlayerJumpStandState::Draw()
{
	m_animation->Draw();
}

PlayerStates PlayerJumpStandState::GetState()
{
	return PlayerStates::JumpStand;
}

void PlayerJumpStandState::PreCollision(GameObject * entity, float deltaTime)
{
	if (entity->getTag() == Tag::ClimbAreaTag)
	{

		auto climbArea = dynamic_cast<ClimbArea*>(entity);
		Box playerBox = m_player->GetBoundingBox();
		if (Collision::getInstance()->isColliding(playerBox, climbArea->GetBoundingBox()))
		{
			m_player->m_canClimb = true;
			m_climbArea = climbArea;
		}
	}
}

void PlayerJumpStandState::OnCollision(GameObject* entity, float deltaTime)
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


bool PlayerJumpStandState::isFalling()
{
	return m_travelledJumpDistance >= m_longestJumpDistance;
}


float PlayerJumpStandState::getInitialY()
{
	return m_initialY;
}

void PlayerJumpStandState::setTravelledJumpDistance(float value)
{
	m_travelledJumpDistance = value;
}

float PlayerJumpStandState::getTravelledJumpDistance()
{
	return m_travelledJumpDistance;
}

float PlayerJumpStandState::getLongestJumpDistance()
{
	return m_longestJumpDistance;
}

#include "stdafx.h"
#include "PlayerStandingState.h"

#define IDLE_TIME 1500
constexpr auto idle_sprite_offset = 3;

PlayerStandingState::PlayerStandingState(Player* player, Animation* animation, Animation* standAndLookAroundAnimadtion)
{
	m_player = player;
	m_animationStand = animation;
	m_animation = animation;
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);

	m_animationStandLookAround = standAndLookAroundAnimadtion;
	m_animationStandLookAround->setPositionX(m_player->getPosition().x);
	m_animationStandLookAround->setPositionY(m_player->getPosition().y - idle_sprite_offset);

	if (m_player->getIsFacingRight() == false)
	{
		m_animation->setFlipHorizontal(true);
	}
	else {
		m_animation->setFlipHorizontal(false);
	}
}


PlayerStandingState::~PlayerStandingState()
{
}

void PlayerStandingState::Update(float deltaTime)
{
	if (m_idleTime >= IDLE_TIME)
	{
		if (m_isIdling01 == false)
		{
			m_animationStandLookAround->Reset();
			m_animation = m_animationStandLookAround;
			if (m_player->getIsFacingRight() == false)
			{
				m_animation->setFlipHorizontal(true);
			}
			else {
				m_animation->setFlipHorizontal(false);
			}
			m_isIdling01 = true;
		}

		m_idleTime = 0;
	}
	else
	{
		m_idleTime += deltaTime;
	}

	if (m_isIdling01 == true) // Idle 01's animation is a bit lower than the default stand. Render it a bit up.
	{
		m_animation->setPositionX(m_player->getPosition().x);
		m_animation->setPositionY(m_player->getPosition().y - idle_sprite_offset);
		m_animation->Update(deltaTime);
	}
	else // Default stand
	{
		m_animation->setPositionX(m_player->getPosition().x);
		m_animation->setPositionY(m_player->getPosition().y);
		m_animation->Update(deltaTime);
	}

	// Prevent moving when pressing both A and D keys.
	if (KeyboardInput::GetInstance()->isKeyDown(VK_A) && KeyboardInput::GetInstance()->isKeyDown(VK_D))
	{
		return;
	}
	if (KeyboardInput::GetInstance()->isKeyReleased(VK_A) || KeyboardInput::GetInstance()->isKeyReleased(VK_D))
	{
		m_player->changeState(PlayerStates::Moving);
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
		if (m_player->m_canClimb)
		{
			m_player->changeState(PlayerStates::Climb);
			auto climbState = dynamic_cast<PlayerClimbState*>(m_player->getCurrentState());
			climbState->attachClimbArea(m_climbArea);
		}
		else
		{
			m_player->changeState(PlayerStates::LookUp);
		}
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
	if (!m_player->m_isOnGround)
	{
		m_player->changeState(PlayerStates::JumpStand);
		auto jumpState = dynamic_cast<PlayerJumpStandState*>(m_player->getCurrentState());
		jumpState->setTravelledJumpDistance(jumpState->getLongestJumpDistance());
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

void PlayerStandingState::PreCollision(GameObject * entity, float deltaTime)
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

	if (entity->getTag() == Tag::VerticleWallTag)
	{
		float normalX, normalY;
		auto result = Collision::getInstance()->SweptAABB(m_player->GetBoundingBox(), dynamic_cast<VerticalWall*>(entity)->GetBoundingBox(), normalX, normalY, deltaTime);
		if (!result.isCollide)
		{
			m_player->m_canMoveLeft = m_player->m_canMoveRight = true;
		}
		if (Collision::getInstance()->isColliding(m_player->GetBoundingBox(), dynamic_cast<VerticalWall*>(entity)->GetBoundingBox()))
		{
			if (dynamic_cast<VerticalWall*>(entity)->left() < m_player->left())
			{
				m_player->m_canMoveLeft = false;
				m_player->m_canMoveRight = true;
			}
			if (dynamic_cast<VerticalWall*>(entity)->left() > m_player->right())
			{
				m_player->m_canMoveLeft = true;
				m_player->m_canMoveRight = false;
			}
		}
	}
	if (entity->getTag() == Tag::BrickTag) // TODO: For falling if goes out of bricks.
	{
		auto brick = dynamic_cast<FloatingBrick*>(entity);
		Box playerBox = m_player->GetBoundingBox();
		playerBox.y -= 30;
		playerBox.height += 30;
		if (Collision::getInstance()->isColliding(playerBox, brick->GetBoundingBox()))
		{
			if (brick->getStatus() == Status::NotAllow)
			{
				//m_player->setPosition(D3DXVECTOR2(m_player->getPosition().x, brick->getPosition().y - (brick->getHeight() + 5)));
				m_player->changeState(PlayerStates::JumpStand);
				auto jumpState = dynamic_cast<PlayerJumpStandState*>(m_player->getCurrentState());
				jumpState->setTravelledJumpDistance(jumpState->getLongestJumpDistance());
				return;
			}
		}
	}
}

void PlayerStandingState::OnCollision(GameObject * entity, float deltaTime)
{
	if (entity->getTag() == Tag::ClimbAreaTag)
	{
		if (entity == m_climbArea)
		{
			auto climbArea = dynamic_cast<ClimbArea*>(entity);
			Box playerBox = m_player->GetBoundingBox();
			if (!Collision::getInstance()->isColliding(playerBox, climbArea->GetBoundingBox()))
			{
				m_player->m_canClimb = false;
			}
		}
	}

	if (entity->getTag() == Tag::GroundTag)
	{
		auto ground = dynamic_cast<Ground*>(entity);
		Box playerBox = m_player->GetBoundingBox();
		playerBox.y -= 50;
		playerBox.height += 150;
		if (Collision::getInstance()->isColliding(playerBox, ground->GetBoundingBox()))
		{
			//OutputDebugString(L"[INFO] Stading State is colliding with ground. \n");
			m_player->m_isOnGround = true;
		}
	}
	if (entity->getTag() == Tag::BrickTag)
	{
		auto brick = dynamic_cast<FloatingBrick*>(entity);
		Box playerBox = m_player->GetBoundingBox();
		playerBox.y -= 50;
		playerBox.height += 150;
		if (Collision::getInstance()->isColliding(playerBox, brick->GetBoundingBox()))
		{
			//OutputDebugString(L"[INFO] Stading State is colliding with brick. \n");
			m_player->m_isOnGround = true;
		}
	}
}

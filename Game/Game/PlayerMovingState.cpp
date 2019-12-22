#include "stdafx.h"
#include "PlayerMovingState.h"
#define SPRITE_OFFSET 25 // For now, I have no idea why moving animation is render lower than standing animation. So minus this offset to bring this animation back up.
PlayerMovingState::PlayerMovingState(Player * player, Animation * animation)
{
	m_player = player;
	m_animation = animation;
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y - SPRITE_OFFSET);
}

PlayerMovingState::~PlayerMovingState()
{
}

void PlayerMovingState::Update(float deltaTime)
{
	// Prevent moving when pressing both A and D keys.
	if (KeyboardInput::GetInstance()->isKeyDown(VK_A) && KeyboardInput::GetInstance()->isKeyDown(VK_D))
	{
		m_player->changeState(PlayerStates::Standing);
		//m_animation->Reset();
		return;
	}

	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y - SPRITE_OFFSET);
	m_animation->Update(deltaTime);

	if (m_player->getIsFacingRight() == false)
	{
		m_animation->setFlipHorizontal(true);
	}
	if (m_player->getIsFacingRight() == true)
	{
		m_animation->setFlipHorizontal(false);
	}

	if (KeyboardInput::GetInstance()->isKeyReleased(VK_D) ||
		KeyboardInput::GetInstance()->isKeyReleased(VK_A))
	{
		if (KeyboardInput::GetInstance()->isKeyDown(VK_D) || KeyboardInput::GetInstance()->isKeyDown(VK_A))
		{
			m_player->changeState(PlayerStates::Moving);
			return;
		}
		m_player->changeState(PlayerStates::Standing);
		return;
	}

	if (KeyboardInput::GetInstance()->isKeyTriggered(VK_SPACE))
	{
		m_player->changeState(PlayerStates::JumpMoving);
		return;
	}

	// From Stand to Attack (swinging the sword).
	if (KeyboardInput::GetInstance()->isKeyTriggered(VK_J))
	{
		m_player->changeState(PlayerStates::MoveAttack);
		return;
	}
	// From Stand to Attack by Throwing apples
	if (KeyboardInput::GetInstance()->isKeyTriggered(VK_K))
	{
		m_player->changeState(PlayerStates::MoveThrow);
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

void PlayerMovingState::Draw()
{
	m_animation->Draw();
}

PlayerStates PlayerMovingState::GetState()
{
	return PlayerStates::Moving;
}

void PlayerMovingState::PreCollision(GameObject * entity, float deltaTime)
{
	//if (entity->getTag() == Tag::GroundTag)
	//{
	//	auto ground = dynamic_cast<Ground*>(entity);
	//	Box playerBox = m_player->GetBoundingBox();
	//	//playerBox.y -= 50;
	//	playerBox.height += 10;
	//	if (Collision::getInstance()->isColliding(playerBox, ground->GetBoundingBox()))
	//	{
	//		m_player->m_isOnGround = true;
	//	}
	//}

	if (entity->getTag() == Tag::VerticleWallTag)
	{
		float normalX, normalY;
		auto result = Collision::getInstance()->SweptAABB(m_player->GetBoundingBox(), dynamic_cast<VerticalWall*>(entity)->GetBoundingBox(), normalX, normalY, deltaTime);
		if (result.isCollide)
		{
			if (result.sideCollided == CollisionSide::Right)
			{
				OutputDebugString(L"[INFO] Player is about to collide with Vertical Wall on the left side of the player. \n");
				m_player->m_canMoveLeft = false;
				m_player->m_canMoveRight = true;
			}
			if (result.sideCollided == CollisionSide::Left)
			{
				OutputDebugString(L"[INFO] Player is about to collide with Vertical Wall on the right side of the player. \n");
				m_player->m_canMoveLeft = true;
				m_player->m_canMoveRight = false;
			}
		}
		else
		{
			if (Collision::getInstance()->isColliding(m_player->GetBoundingBox(), dynamic_cast<VerticalWall*>(entity)->GetBoundingBox()))
			{
				OutputDebugString(L"[INFO] Player is colliding with Vertical Wall. \n");
				m_player->m_canMoveLeft = false;
				m_player->m_canMoveRight = false;
			}
		}
	}
}

void PlayerMovingState::OnCollision(GameObject * entity, float deltaTime)
{
	if (entity->getTag() == Tag::GroundTag)
	{
		auto ground = dynamic_cast<Ground*>(entity);
		Box playerBox = m_player->GetBoundingBox();
		playerBox.x += 10;
		playerBox.y += 10;
		playerBox.width -= 10;
		playerBox.height += 10;
		if (Collision::getInstance()->isColliding(playerBox, ground->GetBoundingBox()))
		{
			m_player->m_isOnGround = true;
		}
	}
}

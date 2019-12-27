#include "stdafx.h"
#include "PlayerClimbAttackState.h"

PlayerClimbAttackState::PlayerClimbAttackState(Player* player, Animation* animation)
{
	m_player = player;
	m_animation = animation;
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);
	m_animation->Reset();

	if (m_player->getIsFacingRight() == false)
	{
		m_animation->setFlipHorizontal(true);
	}
	else
	{
		m_animation->setFlipHorizontal(false);
	}

	Sound::getInstance()->play(SoundNames::HIGH_ATTACK_SOUND, false, 1);
}


PlayerClimbAttackState::~PlayerClimbAttackState()
{
}

void PlayerClimbAttackState::attachClimbArea(ClimbArea * climbArea)
{
	m_climbingArea = climbArea;
}

void PlayerClimbAttackState::Update(float deltaTime)
{
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);
	m_animation->Update(deltaTime);

	if (m_animation->getIsFinished() == true)
	{
		if (KeyboardInput::GetInstance()->isKeyDown(PlayerInputs::MOVE_LEFT) || 
			KeyboardInput::GetInstance()->isKeyDown(PlayerInputs::MOVE_RIGHT)) 
		{
			m_player->changeState(PlayerStates::Moving);
			return;
		}
		m_player->changeState(PlayerStates::Climb);
		auto climbState = dynamic_cast<PlayerClimbState*>(m_player->getCurrentState());
		climbState->attachClimbArea(m_climbingArea);
		return;
	}
}

void PlayerClimbAttackState::Draw()
{
	m_animation->Draw();
}

PlayerStates PlayerClimbAttackState::GetState()
{
	return PlayerStates::ClimbAttack;
}

void PlayerClimbAttackState::PreCollision(GameObject * entity, float deltaTime)
{
}

void PlayerClimbAttackState::OnCollision(GameObject * entity, float deltaTime)
{
	if (entity->getTag() == Tag::MustaheGuardTag)
	{
		auto guard = dynamic_cast<MustacheGuard*>(entity);
		if (Collision::getInstance()->isColliding(m_player->GetBoundingBox(), guard->GetBoundingBox()))
		{
			OutputDebugString(L"[INFO] Player is colliding with Mustache Guard. \n");
			if (m_isAttackingHit == false && guard->getCurrentHealth() > 0.0f)
			{
				dynamic_cast<MustacheGuard*>(entity)->takeDamage(5);
				dynamic_cast<MustacheGuard*>(entity)->isHit();
				m_isAttackingHit = true;
			}
		}
	}
	if (entity->getTag() == Tag::ThinGuardTag)
	{
		auto guard = dynamic_cast<ThinGuard*>(entity);
		if (Collision::getInstance()->isColliding(m_player->GetBoundingBox(), guard->GetBoundingBox()))
		{
			OutputDebugString(L"[INFO] Player is colliding with Thin Guard. \n");
			if (m_isAttackingHit == false && guard->getCurrentHealth() > 0.0f)
			{
				dynamic_cast<ThinGuard*>(entity)->takeDamage(5);
				dynamic_cast<ThinGuard*>(entity)->isHit();
				m_isAttackingHit = true;
			}
		}
	}
	if (entity->getTag() == Tag::BatTag)
	{
		auto bat = dynamic_cast<Bat*>(entity);
		if (Collision::getInstance()->isColliding(m_player->GetBoundingBox(), bat->GetBoundingBox()))
		{
			OutputDebugString(L"[INFO] Player is colliding with BAT. \n");
			if (m_isAttackingHit == false && bat->getCurrentHealth() > 0.0f)
			{
				dynamic_cast<Bat*>(entity)->takeDamage(5);
				m_isAttackingHit = true;
			}
		}
	}
	if (entity->getTag() == Tag::SkeletonTag)
	{
		auto skeleton = dynamic_cast<Skeleton*>(entity);
		if (Collision::getInstance()->isColliding(m_player->GetBoundingBox(), skeleton->GetBoundingBox()))
		{
			OutputDebugString(L"[INFO] Player is colliding with SKELETON. \n");
			if (m_isAttackingHit == false && skeleton->getCurrentHealth() > 0.0f)
			{
				skeleton->takeDamage(10);
				m_isAttackingHit = true;
			}
		}
	}
}

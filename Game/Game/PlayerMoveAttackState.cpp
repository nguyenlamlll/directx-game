#include "stdafx.h"
#include "PlayerMoveAttackState.h"

#define SPRITE_OFFSET 10

PlayerMoveAttackState::PlayerMoveAttackState(Player* player, Animation* animation)
{
	m_player = player;
	m_animation = animation;
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y - SPRITE_OFFSET);
	m_animation->Reset();

	if (m_player->getIsFacingRight() == true)
	{
		m_animation->setFlipHorizontal(false);
	}
	else
	{
		m_animation->setFlipHorizontal(true);
	}

	Sound::getInstance()->play(SoundNames::HIGH_ATTACK_SOUND, false, 1);
}


PlayerMoveAttackState::~PlayerMoveAttackState()
{
}

void PlayerMoveAttackState::Update(float deltaTime)
{
	if (KeyboardInput::GetInstance()->isKeyDown(PlayerInputs::MOVE_LEFT)) {
		m_animation->setFlipHorizontal(true);
	}
	if (KeyboardInput::GetInstance()->isKeyDown(PlayerInputs::MOVE_RIGHT)) {
		m_animation->setFlipHorizontal(false);
	}

	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y - SPRITE_OFFSET);
	m_animation->Update(deltaTime);

	if (m_animation->getIsFinished() == true)
	{
		if (KeyboardInput::GetInstance()->isKeyDown(PlayerInputs::MOVE_LEFT) || KeyboardInput::GetInstance()->isKeyDown(PlayerInputs::MOVE_RIGHT)) {
			m_player->changeState(PlayerStates::Moving);
			return;
		}
		m_player->changeState(PlayerStates::Standing);
		return;
	}
}

void PlayerMoveAttackState::Draw()
{
	m_animation->Draw();
}

PlayerStates PlayerMoveAttackState::GetState()
{
	return PlayerStates::MoveAttack;
}

void PlayerMoveAttackState::PreCollision(GameObject * entity, float deltaTime)
{
}

void PlayerMoveAttackState::OnCollision(GameObject * entity, float deltaTime)
{
	if (entity->getTag() == Tag::MustaheGuardTag)
	{
		auto guard = dynamic_cast<MustacheGuard*>(entity);
		if (Collision::getInstance()->isColliding(m_player->GetBoundingBox(), guard->GetBoundingBox()))
		{
			OutputDebugString(L"[INFO] Player is colliding with Mustache Guard. \n");
			if (isAttackingHit == false && guard->getCurrentHealth() > 0.0f)
			{
				guard->takeDamage(5);
				guard->isHit();
				isAttackingHit = true;
			}
		}
	}
	if (entity->getTag() == Tag::ThinGuardTag)
	{
		auto guard = dynamic_cast<ThinGuard*>(entity);
		if (Collision::getInstance()->isColliding(m_player->GetBoundingBox(), guard->GetBoundingBox()))
		{
			OutputDebugString(L"[INFO] Player is colliding with Thin Guard. \n");
			if (isAttackingHit == false && guard->getCurrentHealth() > 0.0f)
			{
				guard->takeDamage(5);
				guard->isHit();
				isAttackingHit = true;
			}
		}
	}
	if (entity->getTag() == Tag::BatTag)
	{
		auto bat = dynamic_cast<Bat*>(entity);
		auto batBox = bat->GetBoundingBox();
		batBox.x -= 20;
		batBox.width += 30;
		if (Collision::getInstance()->isColliding(m_player->GetBoundingBox(), batBox))
		{
			OutputDebugString(L"[INFO] Player is colliding with BAT. \n");
			if (isAttackingHit == false && bat->getCurrentHealth() > 0.0f)
			{
				bat->takeDamage(5);
				isAttackingHit = true;
			}
		}
	}
	if (entity->getTag() == Tag::SkeletonTag)
	{
		auto skeleton = dynamic_cast<Skeleton*>(entity);
		if (Collision::getInstance()->isColliding(m_player->GetBoundingBox(), skeleton->GetBoundingBox()))
		{
			OutputDebugString(L"[INFO] Player is colliding with SKELETON. \n");
			if (isAttackingHit == false && skeleton->getCurrentHealth() > 0.0f)
			{
				skeleton->takeDamage(10);
				isAttackingHit = true;
			}
		}
	}
}

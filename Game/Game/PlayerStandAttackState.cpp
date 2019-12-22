#include "stdafx.h"
#include "PlayerStandAttackState.h"

constexpr auto sprite_offset = 12;

PlayerStandAttackState::PlayerStandAttackState(Player* player, Animation* animation)
{
	m_player = player;
	m_animation = animation;
	m_animation->Reset();
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y - sprite_offset);
	if (m_player->getIsFacingRight() == true)
	{
		m_animation->setFlipHorizontal(false);
	}
	if (m_player->getIsFacingRight() == false)
	{
		m_animation->setFlipHorizontal(true);
	}

	isAttackingHit = false;
	
	Sound::getInstance()->play(SoundNames::HIGH_ATTACK_SOUND, false, 1);
}


PlayerStandAttackState::~PlayerStandAttackState()
{
}

void PlayerStandAttackState::Update(float deltaTime)
{
	if (KeyboardInput::GetInstance()->isKeyDown(VK_A)) {
		m_animation->setFlipHorizontal(true);
	}
	if (KeyboardInput::GetInstance()->isKeyDown(VK_D)) {
		m_animation->setFlipHorizontal(false);
	}

	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y - sprite_offset);
	m_animation->Update(deltaTime);

	if (m_animation->getIsFinished() == true) 
	{
		if (KeyboardInput::GetInstance()->isKeyDown(VK_A) || KeyboardInput::GetInstance()->isKeyDown(VK_D)) {
			m_player->changeState(PlayerStates::Moving);
			return;
		}
		m_player->changeState(PlayerStates::Standing);
		return;
	}
}

void PlayerStandAttackState::Draw()
{
	m_animation->Draw();
}

PlayerStates PlayerStandAttackState::GetState()
{
	return PlayerStates::StandAttack;
}

void PlayerStandAttackState::PreCollision(GameObject * entity, float deltaTime)
{
}

void PlayerStandAttackState::OnCollision(GameObject* entity, float deltaTime)
{
	if (entity->getTag() == Tag::MustaheGuardTag)
	{
		auto guard = dynamic_cast<MustacheGuard*>(entity);
		if (Collision::getInstance()->isColliding(m_player->GetBoundingBox(), guard->GetBoundingBox()))
		{
			OutputDebugString(L"[INFO] Player is colliding with Mustache Guard. \n");
			if (isAttackingHit == false && guard->getCurrentHealth() > 0.0f)
			{
				dynamic_cast<MustacheGuard*>(entity)->takeDamage(5);
				dynamic_cast<MustacheGuard*>(entity)->isHit();
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
				dynamic_cast<ThinGuard*>(entity)->takeDamage(5);
				dynamic_cast<ThinGuard*>(entity)->isHit();
				isAttackingHit = true;
			}
		}
	}
	if (entity->getTag() == Tag::BatTag)
	{
		auto bat = dynamic_cast<Bat*>(entity);
		if (Collision::getInstance()->isColliding(m_player->GetBoundingBox(), bat->GetBoundingBox()))
		{
			OutputDebugString(L"[INFO] Player is colliding with BAT. \n");
			if (isAttackingHit == false && bat->getCurrentHealth() > 0.0f)
			{
				dynamic_cast<Bat*>(entity)->takeDamage(5);
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

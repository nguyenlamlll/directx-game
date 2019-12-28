#include "stdafx.h"
#include "PlayerSitDownAttack.h"

constexpr auto sprite_offset = 7;

PlayerSitDownAttack::PlayerSitDownAttack(Player* player, Animation* animation)
{
	m_player = player;
	m_animation = animation;
	m_animation->Reset();
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y + sprite_offset);

	if (m_player->getIsFacingRight() == false)
	{
		m_animation->setFlipHorizontal(true);
	}
	else {
		m_animation->setFlipHorizontal(false);
	}

	Sound::getInstance()->play(SoundNames::LOW_ATTACK_SOUND, false, 1);
}


PlayerSitDownAttack::~PlayerSitDownAttack()
{
}

void PlayerSitDownAttack::Update(float deltaTime)
{
	// From Sit Down back to Standing
	if (KeyboardInput::GetInstance()->isKeyReleased(PlayerInputs::SIT_DOWN))
	{
		m_player->changeState(PlayerStates::Standing);
		return;
	}



	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y + sprite_offset);
	m_animation->Update(deltaTime);

	if (m_animation->getIsFinished() == true)
	{
		m_player->changeState(PlayerStates::SitDown);
		dynamic_cast<PlayerSitDownState*>(m_player->getCurrentState())->setIsFixedSittingDown(true);
		return;
	}
}

void PlayerSitDownAttack::Draw()
{
	m_animation->Draw();
}

PlayerStates PlayerSitDownAttack::GetState()
{
	return PlayerStates::SitDownAttack;
}

void PlayerSitDownAttack::PreCollision(GameObject * entity, float deltaTime)
{
}

void PlayerSitDownAttack::OnCollision(GameObject* entity, float deltaTime)
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

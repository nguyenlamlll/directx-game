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
		if (Collision::getInstance()->isColliding(m_player->GetBoundingBox(), dynamic_cast<MustacheGuard*>(entity)->GetBoundingBox()))
		{
			OutputDebugString(L"[INFO] Player is colliding with Mustache Guard. \n");
			if (isAttackingHit == false)
			{
				dynamic_cast<MustacheGuard*>(entity)->takeDamage(5);
				dynamic_cast<MustacheGuard*>(entity)->isHit();
				isAttackingHit = true;
			}
		}
	}
	if (entity->getTag() == Tag::ThinGuardTag)
	{
		if (Collision::getInstance()->isColliding(m_player->GetBoundingBox(), dynamic_cast<ThinGuard*>(entity)->GetBoundingBox()))
		{
			OutputDebugString(L"[INFO] Player is colliding with Thin Guard. \n");
			if (isAttackingHit == false)
			{
				dynamic_cast<ThinGuard*>(entity)->takeDamage(5);
				dynamic_cast<ThinGuard*>(entity)->isHit();
				isAttackingHit = true;
			}
		}
	}
}

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
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y - SPRITE_OFFSET);
	m_animation->Update(deltaTime);

	if (KeyboardInput::GetInstance()->isKeyDown(VK_A)) {
		m_animation->setFlipHorizontal(true);
	}
	if (KeyboardInput::GetInstance()->isKeyDown(VK_D)) {
		m_animation->setFlipHorizontal(false);
	}

	if (KeyboardInput::GetInstance()->isKeyReleased(VK_D) ||
		KeyboardInput::GetInstance()->isKeyReleased(VK_A))
	{
		m_player->changeState(PlayerStates::Standing);
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

void PlayerMovingState::OnCollision(GameObject * entity, float deltaTime)
{
}

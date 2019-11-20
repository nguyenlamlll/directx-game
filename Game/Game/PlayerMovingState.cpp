#include "stdafx.h"
#include "PlayerMovingState.h"

PlayerMovingState::PlayerMovingState(Player * player, Animation * animation)
{
	m_player = player;
	m_animation = animation;
}

PlayerMovingState::~PlayerMovingState()
{
}

void PlayerMovingState::Update(float deltaTime)
{
	if (KeyboardInput::GetInstance()->isKeyReleased(VK_D) ||
		KeyboardInput::GetInstance()->isKeyReleased(VK_A))
	{
		m_player->changeState(PlayerStates::Standing);
	}
	if (KeyboardInput::GetInstance()->isKeyTriggered(VK_J)) {
		OutputDebugString(L"\n[INFO] J key is just triggered. \n");
		m_animation->setFlipHorizontal(!m_animation->getFlipHorizontal());
	}

	//m_animation->setPositionX(m_player->getPosition().x);
	//m_animation->setPositionY(m_player->getPosition().y);
	//m_animation->Update(deltaTime);
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

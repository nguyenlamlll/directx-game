#include "stdafx.h"
#include "PlayerStandLookAround.h"

PlayerStandLookAround::PlayerStandLookAround(Player* player, Animation* animation)
{
	m_player = player;
	m_animation = animation;
}

PlayerStandLookAround::~PlayerStandLookAround()
{
}

void PlayerStandLookAround::Update(float deltaTime)
{
	if (KeyboardInput::GetInstance()->isKeyUp(VK_D))
	{
		//m_player->changeState(PlayerStates::Standing);
	}
	if (KeyboardInput::GetInstance()->isKeyDown(VK_J)) {
		m_animation->setFlipHorizontal(!m_animation->getFlipHorizontal());
	}

	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);
	m_animation->Update(deltaTime);
}

void PlayerStandLookAround::Draw()
{
	m_animation->Draw();
}

PlayerStates PlayerStandLookAround::GetState()
{
	return PlayerStates::StandingLookAround;
}

void PlayerStandLookAround::PreCollision(GameObject * entity, float deltaTime)
{
}

void PlayerStandLookAround::OnCollision(GameObject* entity, float deltaTime)
{
}

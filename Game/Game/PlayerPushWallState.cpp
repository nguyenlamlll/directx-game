#include "stdafx.h"
#include "PlayerPushWallState.h"

PlayerPushWallState::PlayerPushWallState(Player* player, Animation* animation)
{
	m_player = player;
	m_animation = animation;
}


PlayerPushWallState::~PlayerPushWallState()
{
}

void PlayerPushWallState::Update(float deltaTime)
{
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);
	m_animation->Update(deltaTime);
}

void PlayerPushWallState::Draw()
{
	m_animation->Draw();
}

PlayerStates PlayerPushWallState::GetState()
{
	return PlayerStates::PushWall;
}

void PlayerPushWallState::PreCollision(GameObject * entity, float deltaTime)
{
}

void PlayerPushWallState::OnCollision(GameObject* entity, float deltaTime)
{
}
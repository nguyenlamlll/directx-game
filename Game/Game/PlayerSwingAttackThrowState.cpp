#include "stdafx.h"
#include "PlayerSwingAttackThrowState.h"

PlayerSwingAttackThrowState::PlayerSwingAttackThrowState(Player* player, Animation* animation)
{
	m_player = player;
	m_animation = animation;
}


PlayerSwingAttackThrowState::~PlayerSwingAttackThrowState()
{
}

void PlayerSwingAttackThrowState::Update(float deltaTime)
{
	m_animation->setPositionX(m_player->getPosition().x);
	m_animation->setPositionY(m_player->getPosition().y);
	m_animation->Update(deltaTime);
}

void PlayerSwingAttackThrowState::Draw()
{
	m_animation->Draw();
}

PlayerStates PlayerSwingAttackThrowState::GetState()
{
	return PlayerStates::SwingAttackThrow;
}

void PlayerSwingAttackThrowState::OnCollision(GameObject* entity, float deltaTime)
{
}

vector<AppleBullet*>* PlayerSwingAttackThrowState::getListBullet() {
	return &list;
}

void PlayerSwingAttackThrowState::createAppleBullet() {

}
void PlayerSwingAttackThrowState::deleteAppleBullet(AppleBullet* apple) {

}
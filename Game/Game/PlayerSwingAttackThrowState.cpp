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
	if (m_animation->getIndexFrame() == 3&& m_animation->getcurTotalTime()>60.f)
		createAppleBullet();
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

//vector<AppleBullet*>* PlayerSwingAttackThrowState::getListBullet() {
//	return &list;
//}

void PlayerSwingAttackThrowState::createAppleBullet() {
	int appleX, appleY;
	if (m_player->getIsFacingRight())
		appleX = m_animation->getPositionX() + 10;
	else
		appleX = m_animation->getPositionX() - 10;
	appleY = m_animation->getPositionY();
	AppleBullet* apple = new AppleBullet(appleX, appleY, 0, 0, m_player->getIsFacingRight());
	m_player->addAppleToList(apple);
}
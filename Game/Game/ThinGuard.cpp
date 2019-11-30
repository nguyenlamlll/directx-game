#include "stdafx.h"
#include "ThinGuard.h"

#define ATTACK_RANGE 80

ThinGuard::ThinGuard()
{
}

ThinGuard::ThinGuard(float x, float y, float width, float height)
	: GameObject(x, y, width, height, Tag::ThinGuardTag)
{
	this->setPosition(D3DXVECTOR2(x, y));

	m_animations[ThinGuardStates::Standing] = new Animation(L"", 1, 1, 1, true, 100.f, D3DCOLOR_XRGB(255, 0, 255));
	m_animations[ThinGuardStates::Standing]->setPositionX(x);
	m_animations[ThinGuardStates::Standing]->setPositionY(y);
	m_animations[ThinGuardStates::Standing]->setFlipHorizontal(true);

	m_animations[ThinGuardStates::Running] = new Animation(L"Resources/animations/enemy/thin-guard/GuardStick1.png", 8, 1, 8, true, 80.f, D3DCOLOR_XRGB(255, 0, 255));
	m_animations[ThinGuardStates::Running]->setPositionX(x);
	m_animations[ThinGuardStates::Running]->setPositionY(y);
	m_animations[ThinGuardStates::Running]->setFlipHorizontal(true);

	m_animations[ThinGuardStates::Attacking] = new Animation(L"Resources/animations/enemy/thin-guard/GuardStick2.png", 6, 1, 6, true, 100.f, D3DCOLOR_XRGB(255, 0, 255));
	m_animations[ThinGuardStates::Attacking]->setPositionX(x);
	m_animations[ThinGuardStates::Attacking]->setPositionY(y);
	m_animations[ThinGuardStates::Attacking]->setFlipHorizontal(true);

	m_animations[ThinGuardStates::BeingHit] = new Animation(L"Resources/animations/enemy/thin-guard/GuardStick3.png", 9, 1, 9, true, 100.f, D3DCOLOR_XRGB(255, 0, 255));
	m_animations[ThinGuardStates::BeingHit]->setPositionX(x);
	m_animations[ThinGuardStates::BeingHit]->setPositionY(y);
	m_animations[ThinGuardStates::BeingHit]->setFlipHorizontal(true);

	m_currentState = ThinGuardStates::Running;
	m_currentAnimation = m_animations[ThinGuardStates::Running];
}


ThinGuard::~ThinGuard()
{
	delete m_animations[ThinGuardStates::Standing];
	delete m_animations[ThinGuardStates::Running];
	delete m_animations[ThinGuardStates::Attacking];
	delete m_animations[ThinGuardStates::BeingHit];
}

void ThinGuard::attachPlayer(Player * player)
{
	m_player = player;
}

void ThinGuard::checkPositionWithPlayer()
{
	float distance = abs(m_player->getPosition().x - x);
	if (distance <= ATTACK_RANGE)
	{
		m_currentState = ThinGuardStates::Attacking;
		m_currentAnimation = m_animations[ThinGuardStates::Attacking];
	}
	else 
	{
		m_currentState = ThinGuardStates::Running;
		m_currentAnimation = m_animations[ThinGuardStates::Running];
	}
}

Box ThinGuard::GetBoundingBox()
{
	Box box;

	box.x = x - width/2;
	box.y = y - height/2;
	box.width = width;
	box.height = height;
	box.vx = vx;
	box.vy = vy;

	return box;
}

void ThinGuard::Update(float deltaTime)
{
	checkPositionWithPlayer();
	switch (m_currentState) 
	{
	case (ThinGuardStates::Standing):
	case (ThinGuardStates::Running):
	{
		
		break;
	}
	}
	m_currentAnimation->Update(deltaTime);
}

void ThinGuard::OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime)
{
}

void ThinGuard::Draw()
{
	m_currentAnimation->Draw();
}

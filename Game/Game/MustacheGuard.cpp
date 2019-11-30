#include "stdafx.h"
#include "MustacheGuard.h"


MustacheGuard::MustacheGuard()
{
}

MustacheGuard::MustacheGuard(float x, float y, float width, float height)
	: GameObject(x, y, width, height, Tag::MustaheGuardTag)
{
	this->setPosition(D3DXVECTOR2(x, y));

	m_animations[MustacheGuardStates::Standing] = new Animation(L"Resources/animations/enemy/mustache-guard/mocking.png", 6, 1, 6, true, 100.f, D3DCOLOR_XRGB(255, 0, 255));
	m_animations[MustacheGuardStates::Standing]->setPositionX(x);
	m_animations[MustacheGuardStates::Standing]->setPositionY(y);
	m_animations[MustacheGuardStates::Standing]->setFlipHorizontal(true);

	m_animations[MustacheGuardStates::Attacking1] = new Animation(L"Resources/animations/enemy/mustache-guard/attack-1.png", 11, 1, 11, true, 100.f, D3DCOLOR_XRGB(255, 0, 255));
	m_animations[MustacheGuardStates::Attacking1]->setPositionX(x);
	m_animations[MustacheGuardStates::Attacking1]->setPositionY(y);
	m_animations[MustacheGuardStates::Attacking1]->setFlipHorizontal(true);

	m_animations[MustacheGuardStates::Attacking2] = new Animation(L"Resources/animations/enemy/mustache-guard/attack-2.png", 6, 1, 6, true, 100.f, D3DCOLOR_XRGB(255, 0, 255));
	m_animations[MustacheGuardStates::Attacking2]->setPositionX(x);
	m_animations[MustacheGuardStates::Attacking2]->setPositionY(y);
	m_animations[MustacheGuardStates::Attacking2]->setFlipHorizontal(true);

	m_animations[MustacheGuardStates::Moving] = new Animation(L"Resources/animations/enemy/mustache-guard/moving.png", 8, 1, 8, true, 100.f, D3DCOLOR_XRGB(255, 0, 255));
	m_animations[MustacheGuardStates::Moving]->setPositionX(x);
	m_animations[MustacheGuardStates::Moving]->setPositionY(y);
	m_animations[MustacheGuardStates::Moving]->setFlipHorizontal(true);

	m_currentState = MustacheGuardStates::Standing;
	m_currentAnimation = m_animations[MustacheGuardStates::Standing];
}


MustacheGuard::~MustacheGuard()
{
	delete m_animations[MustacheGuardStates::Standing];
	delete m_animations[MustacheGuardStates::Attacking1];
	delete m_animations[MustacheGuardStates::Attacking2];
	delete m_animations[MustacheGuardStates::Moving];
}

void MustacheGuard::attachPlayer(Player * player)
{
}

void MustacheGuard::checkPositionWithPlayer()
{

}

Box MustacheGuard::GetBoundingBox()
{
	Box box;

	box.x = x - width / 2;
	box.y = y - height / 2;
	box.width = width;
	box.height = height;
	box.vx = vx;
	box.vy = vy;

	return box;
}

void MustacheGuard::Update(float deltaTime)
{

	m_currentAnimation->Update(deltaTime);
}

void MustacheGuard::OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime)
{
}

void MustacheGuard::Draw()
{
	m_currentAnimation->Draw();
}

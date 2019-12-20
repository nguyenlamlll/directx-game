#include "stdafx.h"
#include "AppleBullet.h"



AppleBullet::AppleBullet(float x, float y, float width, float height, bool isToRight)
	: GameObject(x, y, width, height, Tag::BulletAppleTag){	
	isDead = false;
	
	// Fling
	m_imageFlying = new Animation(L"Resources/Items/PNG/apple-fling_12_12_4.png", 4, 1, 4, true, 100.f);
	m_imageBurst = new Animation(L"Resources/Items/PNG/apple-fling_12_12_4.png", 4, 1, 4, true, 50.f);
	m_imageBurstBoss = new Animation(L"Resources/Items/PNG/apple-fling_12_12_4.png", 4, 1, 4, true, 50.f);
	achorY = x - 20;
	m_image = m_imageFlying;
	if (isToRight)
		vx = 3.5;
	else
		vx = -3.5;
	vy = -2;

	m_image->setPositionX(x);
	m_image->setPositionY(y);
	m_image->setFlipHorizontal(isToRight);

	m_state = BulletAppleFlying;
}

AppleBullet::~AppleBullet() {
	if (m_imageFlying != NULL) { delete m_imageFlying; m_imageFlying = nullptr; }
	if (m_imageBurst != NULL) { delete m_imageBurst; m_imageBurst = nullptr; }
	if (m_imageBurstBoss != NULL) { delete m_imageBurstBoss; m_imageBurstBoss = nullptr; }
}


Box AppleBullet::GetBoundingBox() {
	Box box;

	box.x = x;
	box.y = y;
	box.width = width;
	box.height = height;
	box.vx = vx;
	box.vy = vy;

	return box;
}

D3DXVECTOR2 AppleBullet::getVelocity() {
	D3DXVECTOR2 result(vx, vy);
	return result;
}

void AppleBullet::Update(float deltaTime) {
	if (!isDead) {
		checkPositionBullet();
		switch (m_state)
		{
		case BulletAppleFlying:
			FlyingAction();
			break;
		case BulletAppleBurst:
			BurstAction();
			break;
		case BulletAppleBurstBoss:
			BurstBossAction();
			break;
		default:
			break;
		}
		m_image->Update(deltaTime);
	}
}

void AppleBullet::checkPositionBullet() {
	if (this->getPosition().y <= achorY)
		vy = 2;
	if (abs(this->getPosition().y - achorY) >= 200)
		BurstAction();
}

void AppleBullet::FlyingAction() {
	switch (m_state)
	{
	case BulletAppleFlying:
		x += vx;
		y += vy;
		m_image->setPositionX(x);
		m_image->setPositionY(y);
		break;
	default:
		m_imageFlying->Reset();
		m_image = m_imageFlying;
		m_image->setPositionX(x);
		m_image->setPositionY(y);
		m_state = BulletAppleFlying;
		break;
	}
}

void AppleBullet::BurstAction() {
	switch (m_state)
	{
	case BulletAppleBurst:
		if (m_image->getIsFinished())
		{
			isDead = true;
		}
		break;
	default:
		vx = vy = 0;
		m_imageBurst->Reset();
		m_image = m_imageBurst;
		m_image->setPositionX(this->x);
		m_image->setPositionY(this->y);
		m_state = BulletAppleBurst;
		break;
	}
}

void AppleBullet::BurstBossAction() {
	switch (m_state)
	{
	case BulletAppleBurstBoss:
		if (m_image->getIsFinished())
		{
			isDead = true;
		}
		break;
	default:
		vx = vy = 0;
		m_imageBurstBoss->Reset();
		m_image = m_imageBurstBoss;
		m_image->setPositionX(this->x);
		m_image->setPositionY(this->y);
		m_state = BulletAppleBurstBoss;
		break;
	}
}

bool AppleBullet::getIsDead() {
	return isDead;
}


void AppleBullet::Draw() {
	if (!isDead)
		m_image->Draw();
}


void AppleBullet::OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime) {
	// to do change status type when happen collision
}





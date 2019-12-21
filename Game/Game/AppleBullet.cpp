#include "stdafx.h"
#include "AppleBullet.h"



AppleBullet::AppleBullet(float x, float y, float width, float height, bool isToRight)
	: GameObject(x, y, width, height, Tag::BulletAppleTag){	
	isDead = false;
	isChangeList = false;
	
	// Fling
	m_imageFlying = new Animation(L"Resources/Items/PNG/apple-fling_12_12_4.png", 4, 1, 4, true, 100.f);
	m_imageBurst = new Animation(L"Resources/Items/PNG/apple-burst_31_27_6.png", 6, 1, 6, false, 60.f);
	m_imageBurstBoss = new Animation(L"Resources/Items/PNG/burst-boss-apple_45_50_20.png", 20, 1, 20, false, 30.f);
	achorY = y - 20;
	m_isFacingRight = isToRight;
	m_image = m_imageFlying;
	if (m_isFacingRight)
		vx = 14.0f;
	else
		vx = -14.0f;
	vy = -2.5f;

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

bool AppleBullet::getIsChangeList() {
	return isChangeList;
}

void AppleBullet::setIsChangeList() {
	isChangeList - true;
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
			break;
		default:
			break;
		}
		m_image->Update(deltaTime);
	}
}

void AppleBullet::checkPositionBullet() {
	if (m_image->getPositionY()<= achorY)
		vy = 6.5f;
	if (abs(m_image->getPositionY() - achorY) >= 200)
		isDead = true;
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

void AppleBullet::BurstBossAction(GameObject* Obj) {
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
		Obj->OnCollision(Obj, 0);
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

void AppleBullet::OnCollision(GameObject* colliableObject, float deltaTime)
{
	switch (colliableObject->getTag())
	{
	case BatTag: case SkeletonTag: case MustaheGuardTag: case ThinGuardTag: //case VerticleWallTag:
		if (Collision::getInstance()->isCollisionEnemy(this->GetBoundingBox(), colliableObject->GetBoundingBoxForApple()))
		{
			colliableObject->OnCollision(this, deltaTime);
			BurstAction();
		}
		break;
	case BossTag:
		if (Collision::getInstance()->isCollisionEnemy(this->GetBoundingBox(), colliableObject->GetBoundingBox()))
		{
			BurstBossAction(colliableObject);
		}
		break;
	default:
		break;
	}
}





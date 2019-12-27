#include "stdafx.h"
#include "BoneBullet.h"



BoneBullet::BoneBullet(float x, float y, float width, float height, int line)
	: GameObject(x, y, width, height, Tag::BulletBoneTag) {
	isDead = false;
	anchorX = x;
	anchorY = y;
	this->line = line;
	// Fling
	m_imageFlying = new Animation(L"Resources/Enmity/PNG/bone-bullet-flying_16_16_3.png", 3, 1, 3, true, 60.f);
	m_imageBurst = new Animation(L"Resources/Enmity/PNG/burst-bone_35_21_3.png", 3, 1, 3, false, 80.f);
	switch (line)
	{
	case 0:
		m_isFacingRight = true;
		vx = 8.0f;
		vy = 0.0f;
		break;
	case 1:
		m_isFacingRight = true;
		vx = 7.16f;
		vy = -3.58f;
		break;
	case 2:
		m_isFacingRight = true;
		vx = 5.65f;
		vy = -5.65f;
		break;
	case 3:
		m_isFacingRight = true;
		vx = 3.58f;
		vy = -7.16f;
		break;
	case 4:
		m_isFacingRight = false;
		vx = 0.0f;
		vy = -8.0f;
		break;
	case 5:
		m_isFacingRight = false;
		vx = -7.16f;
		vy = -3.58f;
		break;
	case 6:
		m_isFacingRight = false;
		vx = -5.65f;
		vy = -5.65f;
		break;
	case 7:
		m_isFacingRight = false;
		vx = -3.58f;
		vy = -7.16f;
		break;
	case 8:
		m_isFacingRight = false;
		vx = -8.0f;
		vy = 0.0f;
		break;
	case 9:
		m_isFacingRight = false;
		vx = -7.16f;
		vy = 3.58f;
		break;
	case 10:
		m_isFacingRight = false;
		vx = -5.65f;
		vy = 5.65f;
		break;
	case 11:
		m_isFacingRight = false;
		vx = -3.58f;
		vy = 7.16f;
		break;
	case 12:
		m_isFacingRight = true;
		vx = 0.0f;
		vy = 8.0f;
		break;
	case 13:
		m_isFacingRight = true;
		vx = 7.16f;
		vy = 3.58f;
		break;
	case 14:
		m_isFacingRight = true;
		vx = 5.65f;
		vy = 5.65f;
		break;
	case 15:
		m_isFacingRight = true;
		vx = 3.58f;
		vy = 7.16f;
		break;
	default:
		m_isFacingRight = true;
		vx = 3.58f;
		vy = 7.16f;
		break;
	}
	m_image = m_imageFlying;
	
	m_image->setPositionX(x);
	m_image->setPositionY(y);
	m_image->setFlipHorizontal(m_isFacingRight);

	m_state = BoneFlying;
}

BoneBullet::~BoneBullet() {
	if (m_imageFlying != NULL) { delete m_imageFlying; m_imageFlying = nullptr; }
	if (m_imageBurst != NULL) { delete m_imageBurst; m_imageBurst = nullptr; }
}

Box BoneBullet::GetBoundingBox() {
	Box box;

	box.x = x - width / 2;
	box.y = y - height / 2;
	box.width = width;
	box.height = height;
	box.vx = vx;
	box.vy = vy;

	return box;
}

D3DXVECTOR2 BoneBullet::getVelocity() {
	D3DXVECTOR2 result(vx, vy);
	return result;
}

void BoneBullet::Update(float deltaTime) {
	if (!isDead) {
		checkPositionBullet();
		switch (m_state)
		{
		case BoneFlying:
			FlyingAction();
			break;
		case BoneBurst:
			BurstAction();
			break;
		default:
			break;
		}
		m_image->Update(deltaTime);
	}
}

void BoneBullet::Draw() {
	if (!isDead)
		m_image->Draw();
}

void BoneBullet::checkPositionBullet() {
	if (abs(this->getPosition().x - anchorX) > 300 || abs(this->getPosition().y - anchorY) > 300 || (abs(vx) <= 0.2f && abs(vy) <= 0.2f))
		isDead = true;
}

void BoneBullet::FlyingAction() {
	switch (m_state)
	{
	case BoneFlying:
		switch (line)
		{
		case 0:
			vx -= 0.12f;
			break;
		case 1:
			vx -= 0.08f;
			vy += 0.04f;
			break;
		case 2:
			vx -= 0.06f;
			vy += 0.06f;
			break;
		case 3:
			vx -= 0.04f;
			vy += 0.08f;
			break;
		case 4:
			vy += 0.12f;
			break;
		case 5:
			vx += 0.08f;
			vy += 0.04f;
			break;
		case 6:
			vx += 0.06f;
			vy += 0.06f;
			break;
		case 7:
			vx += 0.04f;
			vy += 0.08f;
			break;
		case 8:
			vx += 0.12f;
			break;
		case 9:
			vx += 0.08f;
			vy -= 0.04f;
			break;
		case 10:
			vx += 0.06f;
			vy -= 0.06f;
			break;
		case 11:
			vx += 0.04f;
			vy -= 0.08f;
			break;
		case 12:
			vy -= 0.12f;
			break;
		case 13:
			vx -= 0.08f;
			vy -= 0.04f;
			break;
		case 14:
			vx -= 0.06f;
			vy -= 0.06f;
			break;
		case 15:
			vx -= 0.04f;
			vy -= 0.08f;
			break;
		default:
			vx -= 0.04f;
			vy -= 0.08f;
			break;
		}
		x += vx;
		y += vy;
		m_image->setPositionX(x);
		m_image->setPositionY(y);
		break;
	default:
		m_image = m_imageFlying;
		m_image->setPositionX(x);
		m_image->setPositionY(y);
		m_state = BoneFlying;
		break;
	}
}

void BoneBullet::BurstAction() {
	switch (m_state)
	{
	case BoneBurst:
		if (m_image->getIsFinished())
		{
			isDead = true;
		}
		break;
	default:
		vx = vy = 0;
		m_image = m_imageBurst;
		m_image->setPositionX(this->x);
		m_image->setPositionY(this->y);
		m_state = BoneBurst;
		break;
	}
}


bool BoneBullet::getIsDead() {
	return isDead;
}

void BoneBullet::OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime) {
	// to do change status type when happen collision
}

void BoneBullet::OnCollision(GameObject* colliableObject, float deltaTime)
{
	switch (colliableObject->getTag())
	{
	case PlayerTag:
		if (Collision::getInstance()->isColliding(this->GetBoundingBox(), colliableObject->GetBoundingBox())) {
			auto player = dynamic_cast<Player*>(colliableObject);
			OutputDebugString(L"[INFO] BoneBullet attacks Player.\n");
			if (player->getCurrentState()->GetState() == StandAttack ||
				player->getCurrentState()->GetState() == JumpAttack ||
				player->getCurrentState()->GetState() == SitDownAttack ||
				player->getCurrentState()->GetState() == MoveAttack ||
				player->getCurrentState()->GetState() == SwingAttack) {
				BurstAction();
				// sound
			}
			else {
				player->takeDamage(0.5);
				player->isHit();
				BurstAction();
			}
		}
		break;
	default:
		break;
	}
}





#include "stdafx.h"
#include "Fire.h"

#define LIMIT_FIRE 450

Fire::Fire(float x, float y, float width, float height, Boss* boss) : BulletBoss(x, y, width, height, Tag::FireTag) {
	this->setPosition(D3DXVECTOR2(x, y));
	isDied = false;
	m_boss = boss;

	m_anchorX = x;

	m_image = new Animation(L"Resources/Boss/PNG/fire-moving_100_51_8.png", 8, 1, 8, true, 40.f);
	m_isFacingRight = m_boss->getIsFacingRight();
	m_image->setFlipHorizontal(!m_isFacingRight);

	if (m_isFacingRight)
		this->x = x + 30;
	else
		this->x = x - 30;
	this->y = y + 35;
	m_image->setPositionX(this->x);
	m_image->setPositionY(this->y);
}

Fire::~Fire() {
	if (m_image != NULL) { delete m_image; m_image = nullptr; }
}

Box Fire::GetBoundingBox() {
	Box box;

	box.x = x;
	box.y = y;
	box.width = width;
	box.height = height;
	box.vx = vx;
	box.vy = vy;

	return box;
}

D3DXVECTOR2 Fire::getVelocity() {
	D3DXVECTOR2 result(vx, vy);
	return result;
}

void Fire::Update(float deltaTime) {
	if (!isDead) {
		igniteAction();
		if(!isDead)
			m_image->Update(deltaTime);
	}
}

void Fire::Draw() {
	if (!isDead)
		m_image->Draw();
}

void Fire::igniteAction() {
	if (abs(this->x - m_anchorX) <= LIMIT_FIRE) {
		if (!m_isFacingRight) {
			vx = -2.0f;
		}
		else {
			vx = 2.0f;
		}
		x += vx;
		y += vy;
		m_image->setPositionX(x);
		m_image->setPositionY(y);
	}
	else {
		isDied = true;
		isDead = true;
	}
}

void Fire::OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime) {

}

void Fire::OnCollision(GameObject * object, float deltaTime)
{
	if (object->getTag() == Tag::PlayerTag)
	{
		auto player = dynamic_cast<Player*>(object);
		if (Collision::getInstance()->isColliding(this->GetBoundingBox(), player->GetBoundingBox()))
		{
			if (m_isAttackingHit == false && player->getCurrentHealth() > 0.0f)
			{
				player->takeDamage(0.5);
				player->isHit();
				m_isAttackingHit = true;
			}
		}
	}
}


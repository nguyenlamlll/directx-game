#include "stdafx.h"
#include "Fire.h"

#define LIMIT_FIRE 250

Fire::Fire(float x, float y, float width, float height, bool isFacingRight) : GameObject(x, y, width, height, Tag::FireTag) {
	this->setPosition(D3DXVECTOR2(x, y));
	isDead = false;
	isDied = false;

	m_anchorX = x;

	m_isFacingRight = isFacingRight;

	m_image = new Animation(L"Resources/Boss/PNG/fire-moving_100_51_8.png", 8, 1, 8, true, 40.f);
	m_image->setFlipHorizontal(m_isFacingRight);

	m_image->setPositionX(x);
	m_image->setPositionY(y);
	vx = 0;
	vy = 0;
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
		m_image->Update(deltaTime);
	}
}

void Fire::Draw() {
	if (!isDead)
		m_image->Draw();
}

void Fire::igniteAction() {
	if (abs(this->x - m_anchorX) <= LIMIT_FIRE) {
		if (m_isFacingRight) {
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


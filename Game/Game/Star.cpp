#include "stdafx.h"
#include "Star.h"

Star::Star(float x, float y, float width, float height, bool isFacingRight) : GameObject(x, y, width, height, Tag::StarTag) {
	this->setPosition(D3DXVECTOR2(x, y));
	isDead = false;
	isDied = false;

	m_isFacingRight = isFacingRight;

	m_imageFling= new Animation(L"Resources/Boss/PNG/bullet-star_28_16_3.png", 3, 1, 3, true, 100.f);
	m_imageHit = new Animation(L"Resources/Boss/PNG/burst-star_35_21_3.png", 3, 1, 3, false, 50.f);

	m_image = m_imageFling;
	m_image->setFlipHorizontal(m_isFacingRight);
	
	m_image->setPositionX(x);
	m_image->setPositionY(y);
	vx = 0;
	vy = 0;
	m_state = StarFling;
}

Star::~Star() {
	if (m_imageFling != NULL) { delete m_imageFling; m_imageFling = nullptr; }
	if (m_imageHit != NULL) { delete m_imageHit; m_imageHit = nullptr; }
	if (m_player != NULL) { delete m_player; m_player = nullptr; }
}

Box Star::GetBoundingBox() {
	Box box;

	box.x = x;
	box.y = y;
	box.width = width;
	box.height = height;
	box.vx = vx;
	box.vy = vy;

	return box;
}

D3DXVECTOR2 Star::getVelocity() {
	D3DXVECTOR2 result(vx, vy);
	return result;
}

void Star::Update(float deltaTime) {
	if (!isDead) {
		switch (m_state)
		{
		case StarFling:
			FlingAction();
			break;
		case StarHit:
			HitAction();
			break;
		default:
			break;
		}
		m_image->Update(deltaTime);
	}
}

void Star::Draw() {
	if (!isDead) {
		m_image->Draw();
	}
}

void Star::OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime) {

}

void Star::FlingAction() {
	switch (m_state)
	{
	case StarFling: {
		float max;
		vx = m_player->left() - this->x;
		vy = m_player->top() - this->y;
		max = (abs(vx) > abs(vy)) ? abs(vx) : abs(vy);
		vx = (vx / max)*2;
		vy = (vy / max)*2;
		x += vx;
		y += vy;
		if (vx >= 0)
			m_image->setFlipHorizontal(true);
		else
			m_image->setFlipHorizontal(false);

		m_image->setPositionX(x);
		m_image->setPositionY(y);
		break;
	}

	default:
		m_state = StarFling;
		m_imageFling->Reset();
		m_image = m_imageFling;
		vx = 0;
		vy = 0;
		m_image->setPositionX(x);
		m_image->setPositionY(y);
		break;
	}
}

void Star::HitAction() {
	switch (m_state)
	{
	case StarHit: {
		if (m_image->getIsFinished()) {
			vx = 0;
			vy = 0;
			isDead = true;
		}
		else {
			float max;
			vx = ((m_player->left() + m_player->right()) / 2 - this->x);
			vy = ((m_player->top() + m_player->bottom()) / 2 - this->y);
			max = (abs(vx) > abs(vy)) ? abs(vx) : abs(vy);
			vx = vx / max;
			vy = vy / max;
			x += vx;
			y += vy;
			if (vx >= 0)
				m_image->setFlipHorizontal(true);
			else
				m_image->setFlipHorizontal(false);

			m_image->setPositionX(x);
			m_image->setPositionY(y);
		}
		break;
	}
	default:
		m_state = StarHit;
		m_imageHit->Reset();
		m_image = m_imageHit;
		m_image->setPositionX(x);
		m_image->setPositionY(y);
		isDied = true;
		break;
	}
}

void Star::attachPlayer(Player* player) {
	m_player = player;
}

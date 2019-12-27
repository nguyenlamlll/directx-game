#include "stdafx.h"
#include "Star.h"
#define RANGE_X 10
#define RANGE_Y 15

Star::Star(float x, float y, float width, float height, Boss* boss) : BulletBoss(x, y, width, height, Tag::StarTag) {
	this->setPosition(D3DXVECTOR2(x, y));
	isDied = false;
	m_boss = boss;


	m_imageFling = new Animation(L"Resources/Boss/PNG/bullet-star_28_16_3.png", 3, 1, 3, false, 50.f);
	m_imageHit = new Animation(L"Resources/Boss/PNG/burst-star_35_21_3.png", 3, 1, 3, false, 100.f);

	m_image = m_imageFling;
	m_isFacingRight = m_boss->getIsFacingRight();
	m_image->setFlipHorizontal(false);
	if (!m_isFacingRight)
		this->x = x + 30;
	else
		this->x = x - 30;
	this->y = y - 20;
	m_image->setPositionX(this->x);
	m_image->setPositionY(this->y);
	m_state = StarFling;
}

Star::~Star() {
	if (m_imageFling != NULL) { delete m_imageFling; m_imageFling = nullptr; }
	if (m_imageHit != NULL) { delete m_imageHit; m_imageHit = nullptr; }
	//if (m_player != NULL) { delete m_player; m_player = nullptr; }
}

void Star::attachPlayer(Player* player) {
	m_player = player;
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
		OnInterSerct();
		switch (m_state)
		{
		case StarFling:
			FlyingAction();
			break;
		case StarHit:
			HitAction();
			break;
		default:
			break;
		}
		if (!isDead)
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

void Star::OnCollision(GameObject * object, float deltaTime)
{
	if (object->getTag() == Tag::PlayerTag)
	{
		auto player = dynamic_cast<Player*>(object);
		if (Collision::getInstance()->isColliding(this->GetBoundingBox(), player->GetBoundingBox()))
		{
			auto old = m_player->getPosition();
			auto extraVx = 0.0f;
			if (m_boss->getIsFacingRight() == true)
			{
				extraVx = -0.05;
			}
			else
			{
				extraVx = 0.05;
			}
			m_player->setPosition(D3DXVECTOR2(old.x + extraVx  *deltaTime, old.y));
			auto cameraOldPosition = Camera::getInstance()->getPosition();
			cameraOldPosition.x += extraVx * deltaTime;
			Camera::getInstance()->setPosition(cameraOldPosition);
			Camera::getInstance()->updateCamera();
		}
	}
}

void Star::FlyingAction() {
	switch (m_state)
	{
	case StarFling: {
		float max;
		vx = m_player->left() - this->x;
		vy = m_player->top() - this->y;
		max = (abs(vx) > abs(vy)) ? abs(vx) : abs(vy);
		vx = (vx / max) * 3;
		vy = (vy / max) * 3;
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
		if (!isDead) {
			if (m_image->getIndexFrame() == 2) {
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

void Star::OnInterSerct() {

	if (m_state == StarHit)
		return;

	float rangeX, rangeY;
	rangeX = abs(m_player->getPosition().x - this->x);
	rangeY = abs(m_player->getPosition().y - this->y);

	if (rangeX <= RANGE_X && rangeY <= RANGE_Y)
	{
		HitAction();
	}
}

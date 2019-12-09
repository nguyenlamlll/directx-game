#include "stdafx.h"
#include "Bat.h"

#define ATTACK_RANGE 200

Bat::Bat(float x, float y, float width, float height, float limit_left, float limit_right) : GameObject(x, y, width, height, Tag::BatTag) {
	this->setPosition(D3DXVECTOR2(x, y));
	isDead = false;
	isDied = false;
	isUsed = false;

	m_limit_left = limit_left;
	m_limit_top = y;
	m_limit_right = limit_right;
	m_originalX = x;
	m_originalY = y;

	m_imageSwing = new Animation(L"Resources/Enmity/PNG/bat-01-state_21_26_1.png", 1, 1, 1, true, 40.0f);
	m_imageMoving = new Animation(L"Resources/Enmity/PNG/bat-02-state_21_26_4.png", 4, 1, 4, false, 45.f);
	m_imageFling = new Animation(L"Resources/Enmity/PNG/bat-03-state_34_40_7.png", 7, 1, 7, true, 45.f);
	m_imageBurst = new Animation(L"Resources/Enmity/PNG/burst-bat_88_56_8.png", 8, 1, 8, false, 60.f);

	m_image = m_imageSwing;
	m_image->setPositionX(x);
	m_image->setPositionY(y);
	vx = 0;
	vy = 0;
	m_state = BatSwing;
}

Bat::~Bat() {
	if (m_imageSwing != NULL) { delete m_imageSwing; m_imageSwing = nullptr; }
	if (m_imageMoving != NULL) { delete m_imageMoving; m_imageMoving = nullptr; }
	if (m_imageFling != NULL) { delete m_imageFling; m_imageFling = nullptr; }
	if (m_imageBurst != NULL) { delete m_imageBurst; m_imageBurst = nullptr; }
}

Box Bat::GetBoundingBox() {
	Box box;

	box.x = x;
	box.y = y;
	box.width = width;
	box.height = height;
	box.vx = vx;
	box.vy = vy;

	return box;
}

D3DXVECTOR2 Bat::getVelocity() {
	D3DXVECTOR2 result(vx, vy);
	return result;
}

void Bat::Update(float deltaTime) {
	if (!isDead) {
		checkPositionWithPlayer();
		switch (m_state)
		{
		case BatSwing:
			break;
		case BatMoving:
			MovingAction();
			break;
		case BatFling: {
			FlingAction();
			break;
		}			
		case BatBurst:
			BurstAction();
		default:
			break;
		}
		m_image->Update(deltaTime);
	}
}

void Bat::Draw() {
	if (!isDead)
		m_image->Draw();
}

void Bat::attachPlayer(Player* player)
{
	m_player = player;
}

void Bat::checkPositionWithPlayer()
{
	float distanceX, distanceY;
	distanceX = abs(m_player->left() - this->x);

	distanceY = m_player->top() - this->y;
	if (distanceX <= ATTACK_RANGE && !isUsed)
	{
		if (distanceY > 0 && distanceY <= ATTACK_RANGE) {
			MovingAction();
		}

	}
	if (distanceX >= ATTACK_RANGE && isUsed == true && isDead == false)
	{
		float rangeX, rangeY;
		rangeX = abs(this->x - m_originalX);
		rangeY = abs(this->y - m_originalY);
		if (rangeX <= 20 && rangeY <= 20)
		{
			ResetAction();
		}
		if (abs(distanceY) >= ATTACK_RANGE) {
			//ResetAction();
		}

	}
}

void Bat::OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime) {

}

void Bat::ResetAction() {
	if (!isDead) {
		m_imageSwing->Reset();
		m_image = m_imageSwing;
		m_image->setPositionX(m_originalX);
		m_image->setPositionY(m_originalY);
		vx = 0;
		vy = 0;
		m_state = BatSwing;
		isUsed = false;
	}
}

void Bat::MovingAction() {
	switch (m_state)
	{
	case BatMoving:
		if (m_image->getIsFinished()) {
			m_imageFling->Reset();
			m_image = m_imageFling;
			m_image->setPositionX(this->x);
			m_image->setPositionY(this->y);
			m_anchorX = m_player->getPosition().x;
			m_anchorY = m_player->getPosition().y;
			m_isFacingRight = false;
			m_isFacingUp = false;
			m_state = BatFling;
		}
		break;
	default:
		m_state = BatMoving;
		m_imageMoving->Reset();
		m_image = m_imageMoving;
		m_image->setPositionX(this->x);
		m_image->setPositionY(this->y);
		vy = 10.0f;
		vx = 0;
		y += vy;
		isUsed = true;
		break;
	}
}

void Bat::FlingAction() {
	switch (m_state)
	{
	case BatFling: {
		if (m_isFacingRight == true && m_isFacingUp == true) {
			// up to right
			vx = 2.5f;
			vy = -2.2f;
			if (this->x >= m_limit_right)
			{
				m_isFacingRight = false;
				m_anchorX = m_player->getPosition().x;
				m_anchorY = m_player->getPosition().y;
			}
			if (this->y <= m_limit_top)
				m_isFacingUp = false;
		}

		if (m_isFacingRight == false && m_isFacingUp == true) {
			// up to left
			vx = -2.5f;
			vy = -2.2f;
			if (this->x <= m_limit_left)
			{
				m_isFacingRight = true;
				m_anchorX = m_player->getPosition().x;
				m_anchorY = m_player->getPosition().y;
			}
			if (this->y <= m_limit_top)
				m_isFacingUp = false;
		}

		if (m_isFacingRight == true && m_isFacingUp == false) {
			// down to right
			vx = 2.5f;
			vy = 2.2f;
			if (this->y >= m_anchorY)
				m_isFacingUp = true;
		}

		if (m_isFacingRight == false && m_isFacingUp == false) {
			// down to left
			vx = -2.5f;
			vy = 2.2f;
			if (this->y >= m_anchorY)
				m_isFacingUp = true;
		}
		x += vx;
		y += vy;
		m_image->setPositionX(x);
		m_image->setPositionY(y);

		break;
	}
	default:
		m_state = BatFling;
		m_imageMoving->Reset();
		m_image = m_imageMoving;
		m_image->setPositionX(this->x);
		m_image->setPositionY(this->y);
		isUsed = true;
		break;
	}
}

void Bat::BurstAction() {
	switch (m_state)
	{
	case BatBurst:
		if (m_image->getIsFinished()) {
			isDead = true;
		}
		break;
	default:
		m_state = BatBurst;
		m_imageBurst->Reset();
		m_image = m_imageBurst;
		m_image->setPositionX(this->x);
		m_image->setPositionY(this->y);
		vx = 0;
		vy = 0;
	}
}

//get state
BatState Bat::getState() {
	return m_state;
}

#include "stdafx.h"
#include "Player.h"

Player::Player(float x, float y, float width, float height, LPCWSTR spritePath)
	: GameObject(x, y, width, height)
{
	m_playerSprite = new Sprite(spritePath);
	m_playerSprite->setPositionX(x);
	m_playerSprite->setPositionY(y);

	speed = 0.3f;
}

Player::~Player()
{
	if (m_playerSprite) delete m_playerSprite;
}

void Player::SetControlDevice(ControlDevice device)
{
	m_controlDevice = device;
}

Box Player::GetBoundingBox()
{
	Box box;

	box.x = x;
	box.y = y;
	box.width = width;
	box.height = height;
	box.vx = vx;
	box.vy = vy;

	return box;
}

D3DXVECTOR2 Player::getVelocity()
{
	D3DXVECTOR2 result(vx, vy);
	return result;
}

void Player::Update(float deltaTime)
{
	if (KeyboardInput::GetInstance()->isKeyDown(VK_D)) {
		vx = speed * deltaTime;
	}
	else if (KeyboardInput::GetInstance()->isKeyDown(VK_A)) {
		vx = -speed * deltaTime;
	}
	else
	{
		vx = 0.0f;
	}

	if (KeyboardInput::GetInstance()->isKeyDown(VK_W)) {
		vy = -speed * deltaTime;
	}
	else if (KeyboardInput::GetInstance()->isKeyDown(VK_S)) {
		vy = speed * deltaTime;
	}
	else
	{
		vy = 0.0f;
	}

	m_playerSprite->setPositionX(m_playerSprite->getPositionX() + vx);
	m_playerSprite->setPositionY(m_playerSprite->getPositionY() + vy);

	x = m_playerSprite->getPositionX();
	y = m_playerSprite->getPositionY();

	auto cameraOldPosition = Camera::getInstance()->getPosition();
	cameraOldPosition.x += vx;
	cameraOldPosition.y -= vy;
	Camera::getInstance()->setPosition(cameraOldPosition);
}

void Player::OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime)
{
	for (auto it = colliableObjects->begin(); it != colliableObjects->end(); it++)
	{
		float normalX, normalY;
		auto collisionResult = Collision::getInstance()->SweptAABB(this->GetBoundingBox(), it->second->GetBoundingBox(), normalX, normalY, deltaTime);
		if (collisionResult.isCollide)
		{
			vx = vy = 0;
			OutputDebugString(L"Player collide with something. \n");
		}
	}
}

void Player::Draw()
{
	m_playerSprite->Draw();
}

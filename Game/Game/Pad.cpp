#include "stdafx.h"
#include "Pad.h"


Pad::Pad(float x, float y, float width, float height, LPCWSTR spritePath)
	: GameObject(x, y, width, height)
{
	m_padSprite = new Sprite(spritePath);
	m_padSprite->setPositionX(x);
	m_padSprite->setPositionY(y);

}


Pad::~Pad()
{
}

void Pad::SetControlDevice(ControlDevice device)
{
	m_controlDevice = device;
}

Box Pad::GetBoundingBox()
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

D3DXVECTOR2 Pad::getVelocity()
{
	D3DXVECTOR2 result(vx, vy);
	return result;
}

void Pad::Update(float deltaTime)
{
	switch (m_controlDevice)
	{
	case Mouse:
	{
		if (MouseInput::getInstance()->getCurrentMousePosition().y < m_padSprite->getPositionY()) {
			vy = -.2f*deltaTime;
		}
		else if (MouseInput::getInstance()->getCurrentMousePosition().y > m_padSprite->getPositionY()) {
			vy = .2f*deltaTime;
		}
		else
		{
			vy = 0.0f;
		}
		m_padSprite->setPositionY(m_padSprite->getPositionY() + vy);
		break;
	}
	case Keyboard:
	{
		if (KeyboardInput::GetInstance()->isKeyDown(VK_W)) {
			vy = -.2f*deltaTime;
		}
		else if (KeyboardInput::GetInstance()->isKeyDown(VK_S)) {
			vy = .2f*deltaTime;
		}
		else 
		{
			vy = 0.0f;
		}
		m_padSprite->setPositionY(m_padSprite->getPositionY() + vy);
		break;
	}
	default:
	{
		break;
	}
	}

	// Update positions
	x = m_padSprite->getPositionX();
	y = m_padSprite->getPositionY();
}

void Pad::Draw()
{
	m_padSprite->Draw();
}

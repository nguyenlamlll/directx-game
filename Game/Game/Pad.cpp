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

void Pad::Update(float deltaTime)
{
	switch (m_controlDevice) 
	{
	case Mouse:
	{
		if (MouseInput::getInstance()->getCurrentMousePosition().y < m_padSprite->getPositionY()) {
			//isRightMovingUp = true;
			//isRightMovingDown = false;
			m_padSprite->setPositionY(m_padSprite->getPositionY() - .2f*deltaTime);
		}
		if (MouseInput::getInstance()->getCurrentMousePosition().y > m_padSprite->getPositionY()) {
			//isRightMovingUp = false;
			//isRightMovingDown = true;
			m_padSprite->setPositionY(m_padSprite->getPositionY() + .2f*deltaTime);
		}
		break;
	}
	case Keyboard:
	{
		if (KeyboardInput::GetInstance()->isKeyDown(VK_W)) {
			//isLeftMovingUp = true;
			//isLeftMovingDown = false;
			m_padSprite->setPositionY(m_padSprite->getPositionY() - .2f*deltaTime);
		}
		if (KeyboardInput::GetInstance()->isKeyDown(VK_S)) {
			//isLeftMovingUp = false;
			//isLeftMovingDown = true;
			m_padSprite->setPositionY(m_padSprite->getPositionY() + .2f*deltaTime);
		}
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

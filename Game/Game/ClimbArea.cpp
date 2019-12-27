#include "stdafx.h"
#include "ClimbArea.h"

ClimbArea::ClimbArea(float x, float y, float width, float height, bool isDebug)
	: GameObject(x, y, width, height, Tag::ClimbAreaTag)
{
	this->setPosition(D3DXVECTOR2(x, y));

	m_isDebugVisible = isDebug;
	if (isDebug)
	{
		m_debugSprite = new Sprite(L"Resources/climb-area.png", D3DCOLOR_XRGB(106, 148, 1));
		m_debugSprite->setPositionX(x);
		m_debugSprite->setPositionY(y);
	}
	else
	{
		m_debugSprite = nullptr;
	}
}


ClimbArea::~ClimbArea()
{
	if (m_debugSprite != nullptr)
	{
		delete m_debugSprite;
	}
}

void ClimbArea::setIsDebugVisible(bool value)
{
	m_isDebugVisible = value;
}

Box ClimbArea::GetBoundingBox()
{
	Box box;

	box.x = x - width / 2 + 20;
	box.y = y - height / 2;
	box.width = width - 40;
	box.height = height;
	box.vx = vx;
	box.vy = vy;

	return box;
}

void ClimbArea::Update(float deltaTime)
{
}

void ClimbArea::Draw()
{
	if (m_isDebugVisible == true)
	{
		m_debugSprite->Draw();
	}
}

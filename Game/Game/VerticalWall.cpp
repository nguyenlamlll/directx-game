#include "stdafx.h"
#include "VerticalWall.h"

VerticalWall::VerticalWall(std::string spriteName, float x, float y, float width, float height, float scaleX, float scaleY, bool isDebug)
	: GameObject(x, y, width*scaleX, height*scaleY, Tag::VerticleWallTag)
{
	this->setPosition(D3DXVECTOR2(x, y));

	std::wstring stemp = s2ws(spriteName);
	LPCWSTR result = stemp.c_str();

	m_isDebugVisible = isDebug;
	if (isDebug)
	{
		m_debugSprite = new Sprite(result, D3DCOLOR_XRGB(254, 254, 254));
		m_debugSprite->setPositionX(x);
		m_debugSprite->setPositionY(y);
		m_debugSprite->setScale(D3DXVECTOR3(scaleX, scaleY, 1.0f));

		m_sprite = m_debugSprite;
	}
	else
	{
		m_sprite = nullptr;
	}
}

VerticalWall::~VerticalWall()
{
	delete m_debugSprite;
}

void VerticalWall::setIsDebugVisible(bool value)
{
	m_isDebugVisible = value;
	if (value == true)
	{
		m_sprite = m_debugSprite;
	}
	else
	{
		//m_sprite = m_realSprite;
	}
}

Box VerticalWall::GetBoundingBox()
{
	Box box;

	box.x = x - width / 2;
	box.y = y - height / 2;
	box.width = width;
	box.height = height;
	box.vx = vx;
	box.vy = vy;

	return box;
}

void VerticalWall::Update(float deltaTime)
{
}

void VerticalWall::Draw()
{
	if (m_isDebugVisible)
	{
		m_sprite->Draw();
	}
}

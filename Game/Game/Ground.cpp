#include "stdafx.h"
#include "Ground.h"

Ground::Ground(float x, float y, float width, float height, float scaleX, float scaleY, bool isDebug)
	: GameObject(x, y, width*scaleX, height*scaleY, Tag::GroundTag)
{
	this->setPosition(D3DXVECTOR2(x, y));

	m_isDebugVisible = isDebug;
	if (isDebug)
	{
		m_debugSprite = new Sprite(L"Resources/ground.png", D3DCOLOR_XRGB(254, 254, 254));
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

Ground::~Ground()
{
	delete m_debugSprite;
}

void Ground::setIsDebugVisible(bool value)
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

Box Ground::GetBoundingBox()
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

void Ground::Update(float deltaTime)
{
}

void Ground::Draw()
{
	if (m_isDebugVisible)
	{
		m_sprite->Draw();
	}
}

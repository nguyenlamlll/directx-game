#include "stdafx.h"
#include "ForegroundChains.h"

ForegroundChains::ForegroundChains(float x, float y, float width, float height, float scaleX, float scaleY)
	: GameObject(x, y, width, height, Tag::UnclassifiedTag)
{
	this->setPosition(D3DXVECTOR2(x, y));
	m_sprite = new Sprite(L"Resources/map/foreground-chains.png", D3DCOLOR_XRGB(163, 73, 164));
	m_sprite->setPositionX(x);
	m_sprite->setPositionY(y);
	m_sprite->setScale(D3DXVECTOR3(scaleX, scaleY, 1.0f));

}

ForegroundChains::~ForegroundChains()
{
	delete m_sprite;
}

void ForegroundChains::Update(float deltaTime)
{
	//if (KeyboardInput::GetInstance()->isKeyDown(VK_D))
	//{
	//	m_sprite->setPositionX(m_sprite->getPositionX() - 0.1f * deltaTime);
	//}
	//if (KeyboardInput::GetInstance()->isKeyDown(VK_A))
	//{
	//	m_sprite->setPositionX(m_sprite->getPositionX() + 0.1f * deltaTime);
	//}
}

void ForegroundChains::Draw()
{
	m_sprite->Draw();
}

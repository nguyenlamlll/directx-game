#include "stdafx.h"
#include "ExitDoor.h"


ExitDoor::ExitDoor(float x, float y, float width, float height)
	: GameObject(x, y, width, height, Tag::ExitDoorTag)
{
	this->setPosition(D3DXVECTOR2(x, y));
	m_sprite = new Sprite(L"Resources/map/exit-door.png", D3DCOLOR_XRGB(163, 73, 164));
	m_sprite->setPositionX(x);
	m_sprite->setPositionY(y);
}


ExitDoor::~ExitDoor()
{
	delete m_sprite;
}

Box ExitDoor::GetBoundingBox()
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

void ExitDoor::Update(float deltaTime)
{
}

void ExitDoor::Draw()
{
	m_sprite->Draw();
}

#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject()
{
}

GameObject::GameObject(float x, float y, float width, float height, Tag tag)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	vx = 0;
	vy = 0;
	m_tag = tag;
}


GameObject::~GameObject()
{
}

Box GameObject::GetBoundingBox()
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

void GameObject::Update(float deltaTime)
{
}

void GameObject::OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime)
{
}

void GameObject::Draw()
{
}

void GameObject::setPosition(D3DXVECTOR2 value)
{
	x = value.x;
	y = value.y;
}

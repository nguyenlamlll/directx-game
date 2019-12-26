#include "stdafx.h"
#include "Item.h"

Item::Item(float x, float y, float width, float height) 
	: GameObject(x, y, width, height, Tag::ItemTag) 
{
	status = NonActive;
}

Item::Item(float x, float y, float width, float height, Tag tag)
	: GameObject(x, y, width, height, tag)
{
	status = NonActive;
}

Item::~Item() {
	//if (image != NULL)
	//{
	//	delete image;
	//	image = nullptr;
	//}
}

Box Item::GetBoundingBox() {
	Box box;

	box.x = x;
	box.y = y;
	box.width = width;
	box.height = height;
	box.vx = vx;
	box.vy = vy;

	return box;
}

D3DXVECTOR2 Item::getVelocity() {
	D3DXVECTOR2 result(vx, vy);
	return result;
}

void Item::Update(float deltaTime) {
	OnInterSerct();
	if (!isUsed) 
		NonActiveAction();
	else
		ActiveAction();
	image->Update(deltaTime);
}

void Item::OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime) {

}

void Item::Draw() {
	if (!isDead) {
		image->Draw();
	}
}

void Item::ActiveAction() {
	switch (status)
	{
	case Active:
	{
		if (image->getIsFinished())
			isDead = true;
		break;
	}
	default:
	{
		status = Active;
		vy = 0;
		vx = 0;
		isDied = true;
		isUsed= true;
		break;
	}
	}
}

void Item::NonActiveAction() {

}

int Item::getStatus() {
	return status;
}

void Item::attachPlayer(Player* player)
{
	m_player = player;
}

void Item::OnInterSerct() {
	float rangeX, rangeY;
	rangeX = abs(m_player->getPosition().x - this->x);
	rangeY = abs(m_player->getPosition().y - this->y);

	if (rangeX <= 35 && rangeY <= 35)
	{
		ActiveAction();
	}
}

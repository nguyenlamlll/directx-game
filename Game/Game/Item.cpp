#include "stdafx.h"
#include "Item.h"

Item::Item(float x, float y, float width, float height) : GameObject(x, y, width, height, Tag::ItemTag) {
	status = NonActive;
}

Item::~Item() {
	if (image != NULL)
	{
		delete image;
		image = nullptr;
	}
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
	switch (status)
	{
	case NonActive:
		NonActiveAction();
		image->Update(deltaTime);
		break;
	case Active:
		ActiveAction();
		if (!isDead) {
			image->Update(deltaTime);
		}
		break;
	default:
		break;
	}
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

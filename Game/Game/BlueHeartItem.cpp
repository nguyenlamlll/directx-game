#include "stdafx.h"
#include "BlueHeartItem.h"

BlueHeartItem::BlueHeartItem(float x, float y, float width, float height) : Item(x, y, width, height) {
	this->setPosition(D3DXVECTOR2(x, y));

	isUsed= false;
	isDead = false;
	isDied = false;

	// start marking time
	start_wait = GetTickCount();

	// Ruby
	image = new Animation(L"Resources/Items/PNG/blue-heart_19_26_8.png", 8, 1, 8, false, 40.f);
	image->setPositionX(x);
	image->setPositionY(y);
}

BlueHeartItem::~BlueHeartItem() {

}

void BlueHeartItem::ActiveAction() {
	// when happen collision, change animation, then delete this
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
		image = new Animation(L"Resources/Items/PNG/apple-actived_20_19_4.png", 4, 1, 4, false, 80.f);
		image->setPositionX(this->x);
		image->setPositionY(this->y);
		vy = 0;
		vx = 0;
		isDied = true;
		isUsed= true;
		status = Active;
		break;
	}
	}
}

void BlueHeartItem::NonActiveAction() {
	if (image->getIsFinished())
	{
		// get current time
		DWORD now = GetTickCount();
		if (now - start_wait > 5000)
		{
			// reset animation
			image->Reset();
			// reset start marking time
			start_wait = GetTickCount();
		}
	}
}

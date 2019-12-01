#include "stdafx.h"
#include "GenieFaceItem.h"

GenieFaceItem::GenieFaceItem(float x, float y, float width, float height) : Item(x, y, width, height) {
	this->setPosition(D3DXVECTOR2(x, y));

	isUsed = false;
	isDead = false;
	isDied = false;

	// start marking time
	start_wait = GetTickCount();

	// Ruby
	image = new Animation(L"Resources/Items/PNG/genie-face_45_52_4.png", 4, 1, 4, false, 40.f);
	image->setPositionX(x);
	image->setPositionY(y);
}

GenieFaceItem::~GenieFaceItem() {

}

void GenieFaceItem::ActiveAction() {
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
		image = new Animation(L"Resources/Items/PNG/Explosions-genieFace_43_43_7.png", 5, 1, 5, false, 60.f);
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

void GenieFaceItem::NonActiveAction() {
	if (image->getIsFinished())
	{
		// get current time
		DWORD now = GetTickCount();
		if (now - start_wait > 3000)
		{
			// reset animation
			image->Reset();
			// reset start marking time
			start_wait = GetTickCount();
		}
	}
}

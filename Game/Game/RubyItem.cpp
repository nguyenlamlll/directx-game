#include "stdafx.h"
#include "RubyItem.h"

RubyItem::RubyItem(float x, float y, float width, float height, int indexFrame) : Item(x, y, width, height) {
	this->setPosition(D3DXVECTOR2(x, y));

	isUsed= false;
	isDead = false;
	isDied = false;

	// start marking time
	start_wait = GetTickCount();

	// Ruby
	image = new Animation(L"Resources/Items/PNG/ruby_32_25_9.png", 9, 1, 9, indexFrame, false, 40.f);
	image->setPositionX(x);
	image->setPositionY(y);
}

RubyItem::~RubyItem() {

}

void RubyItem::ActiveAction() {
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
		image = new Animation(L"Resources/Items/PNG/Apple-Ruby-Heart-collision_20_19_5.png", 5, 1, 5, false, 60.f);
		image->setPositionX(this->x);
		image->setPositionY(this->y);
		vy = 0;
		vx = 0;
		isDied = true;
		isUsed = true;
		status = Active;
		break;
	}
	}
}

void RubyItem::NonActiveAction() {
	if (image->getIsFinished())
	{
		// get current time
		DWORD now = GetTickCount();
		if (now - start_wait > 3500)
		{
			// reset animation
			image->Reset();
			// reset start marking time
			start_wait = GetTickCount();
		}
	}
}

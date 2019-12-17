#include "stdafx.h"
#include "AppleItem.h"

AppleItem::AppleItem(float x, float y, float width, float height) : Item(x, y, width, height){
	this->setPosition(D3DXVECTOR2(x, y));

	isUsed = false;
	isDead = false;
	isDied = false;


	// apple
	image = new Animation(L"Resources/Items/PNG/apple_11_11_1.png", 1, 1, 1);
	image->setPositionX(x);
	image->setPositionY(y);
}

AppleItem::~AppleItem() {

}

void AppleItem::ActiveAction() {
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
		status = Active;
		image = new Animation(L"Resources/Items/PNG/apple-actived_20_19_4.png", 4, 1, 4, false, 80.f);
		image->setPositionX(this->x);
		image->setPositionY(this->y);
		vy = 0;
		vx = 0;
		isDied = true;
		isUsed= true;
		break;
	}
	}
}

void AppleItem::NonActiveAction() {
	// do nothing
}
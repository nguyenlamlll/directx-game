#include "stdafx.h"
#include "GenieJarItem.h"

GenieJarItem::GenieJarItem(float x, float y, float width, float height) : Item(x, y, width, height){
	this->setPosition(D3DXVECTOR2(x, y));

	isUsed = false;
	isDead = false;
	isDied = false;

	// start marking time
	start_wait = GetTickCount();

	// Ruby
	image = new Animation(L"Resources/Items/PNG/genie-jar_34_38_1.png", 1, 1, 1);
	image->setPositionX(x);
	image->setPositionY(y);
}

GenieJarItem::~GenieJarItem() {

}

void GenieJarItem::ActiveAction() {
	switch (status)
	{
	case Active:
	{
		// load frame last old
		if (image->getIsFinished()) {
			vy = 0;
			vx = 0;
			image = new Animation(L"Resources/Items/PNG/genie-jar-end_34_38_1.png", 1, 1, 1);
			image->setPositionX(this->x);
			image->setPositionY(this->y-3);
			isDied = true;
			isUsed = true;
		}
		break;
	}
	default:
	{
		//  to do GameSound
		vy = 0;
		vx = 0;
		image = new Animation(L"Resources/Items/PNG/genie-jar_34_38_10.png", 10, 1, 10, false, 70.f);
		image->setPositionX(this->x);
		image->setPositionY(this->y);
		isDied = true;
		isUsed = true;

		status = Active;
		break;
	}
	}
}

void GenieJarItem::NonActiveAction() {
	// do nothing
}

#include "stdafx.h"
#include "GenieFaceItem.h"

GenieFaceItem::GenieFaceItem(float x, float y, float width, float height) : Item(x, y, width, height) {
	this->setPosition(D3DXVECTOR2(x, y));

	isUsed = false;
	isDead = false;
	isDied = false;

	// start marking time
	start_wait = GetTickCount();

	m_imageGenieFace = new Animation(L"Resources/Items/PNG/genie-face_45_52_4.png", 4, 1, 4, false, 150.f);
	m_imageBurst = new Animation(L"Resources/Items/PNG/burst-boss-apple_45_50_20.png", 20, 1, 20, false, 60.f);

	image = m_imageGenieFace;
	image->setPositionX(x);
	image->setPositionY(y);
}

GenieFaceItem::~GenieFaceItem() 
{
	 delete m_imageGenieFace;
	 delete m_imageBurst;
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
		image = m_imageBurst;
		image->setPositionX(this->x);
		image->setPositionY(this->y);
		vy = 0;
		vx = 0;
		isDied = true;
		isUsed = true;
		m_player->m_score += 250;
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

#include "stdafx.h"
#include "RubyItem.h"

RubyItem::RubyItem(float x, float y, float width, float height, int indexFrame) : Item(x, y, width, height) {
	this->setPosition(D3DXVECTOR2(x, y));

	isUsed= false;
	isDead = false;
	isDied = false;

	// start marking time
	start_wait = GetTickCount();

	m_imageInitial = new Animation(L"Resources/Items/PNG/ruby_32_25_9.png", 9, 1, 9, indexFrame, false, 40.f);
	m_imageActivated = new Animation(L"Resources/Items/PNG/apple-actived_20_19_4.png", 4, 1, 4, false, 80.f);
	image = m_imageInitial;
	image->setPositionX(x);
	image->setPositionY(y);
}

RubyItem::~RubyItem() 
{
	delete m_imageInitial;
	delete m_imageActivated;
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
		image = new Animation(L"Resources/Items/PNG/apple-actived_20_19_4.png", 4, 1, 4, false, 80.f);
		image->setPositionX(this->x);
		image->setPositionY(this->y);
		vy = 0;
		vx = 0;
		isDied = true;
		isUsed = true;
		m_player->m_rubyCount += 1;
		m_player->m_score += 150;
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

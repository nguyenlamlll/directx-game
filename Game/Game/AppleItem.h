#pragma once
#include "Item.h"

class AppleItem : public Item
{
protected:
	Animation* m_imageInitial;
	Animation* m_imageUsed;
public:
	AppleItem(float x, float y, float width, float height);
	~AppleItem();

	void ActiveAction();
	void NonActiveAction();

};

#pragma once
#include "Item.h"

class AppleItem : public Item
{
public:
	AppleItem(float x, float y, float width, float height);
	~AppleItem();

	void ActiveAction();
	void NonActiveAction();

};

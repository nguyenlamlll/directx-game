#pragma once
#include "Item.h"

class BlueHeartItem : public Item
{
public:
	BlueHeartItem(float x, float y, float width, float height);
	~BlueHeartItem();

	void ActiveAction();
	void NonActiveAction();

};

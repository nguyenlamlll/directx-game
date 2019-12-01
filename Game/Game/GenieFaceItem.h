#pragma once
#include "Item.h"

class GenieFaceItem : public Item
{
public:
	GenieFaceItem(float x, float y, float width, float height);
	~GenieFaceItem();

	void ActiveAction();
	void NonActiveAction();

};

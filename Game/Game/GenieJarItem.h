#pragma once
#include "Item.h"

class GenieJarItem : public Item
{
public:
	GenieJarItem(float x, float y, float width, float height);
	~GenieJarItem();

	void ActiveAction();
	void NonActiveAction();

};

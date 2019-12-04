#pragma once
#include "Item.h"

class RubyItem : public Item
{
public:
	RubyItem(float x, float y, float width, float height, int indexFrame);
	~RubyItem();

	void ActiveAction();
	void NonActiveAction();

};

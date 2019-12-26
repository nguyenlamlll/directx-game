#pragma once
#include "Item.h"

class RubyItem : public Item
{
private:
	Animation* m_imageInitial;
	Animation* m_imageActivated;
public:
	RubyItem(float x, float y, float width, float height, int indexFrame);
	~RubyItem();

	void ActiveAction();
	void NonActiveAction();

};

#pragma once
#include "Item.h"

class BlueHeartItem : public Item
{
private:
	Animation* m_imageInitial;
	Animation* m_imageActivated;
public:
	BlueHeartItem(float x, float y, float width, float height);
	~BlueHeartItem();

	void ActiveAction();
	void NonActiveAction();

};

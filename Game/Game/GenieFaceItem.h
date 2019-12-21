#pragma once
#include "Item.h"

class GenieFaceItem : public Item
{
private:
	Animation* m_imageGenieFace;
	Animation* m_imageBurst;
public:
	GenieFaceItem(float x, float y, float width, float height);
	~GenieFaceItem();

	void ActiveAction();
	void NonActiveAction();

};

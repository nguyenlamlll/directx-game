#pragma once
#include "Item.h"
#include "AladdinGlobal.h"
class GenieJarItem : public Item
{
protected:
	Animation* m_imageGenieJarInitial;
	Animation* m_imageGenieJar;
	Animation* m_imageGenieJarUsed;
public:
	GenieJarItem(float x, float y, float width, float height);
	~GenieJarItem();

	void ActiveAction();
	void NonActiveAction();

};

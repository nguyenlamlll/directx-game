#pragma once
#include "Collision.h"
#include <map>
enum Tag {
	PlayerTag,
	GroundTag,
	PadTag,
	UnclassifiedTag
};
class GameObject
{
protected:
	float x, y;
	float width, height;
	float vx, vy;

	Tag m_tag;
public:
	GameObject();
	GameObject(float x, float y, float width, float height, Tag tag);
	virtual ~GameObject();

	virtual Box GetBoundingBox();

	virtual void Update(float deltaTime);
	void OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime);
	virtual void Draw();

	virtual void setPosition(D3DXVECTOR2);
	virtual D3DXVECTOR2 getPosition() 
	{
		return D3DXVECTOR2(x, y);
	}

	virtual Tag getTag() { return m_tag; }
	virtual float getWidth() { return width; }
	virtual float getHeight() { return height; }
};


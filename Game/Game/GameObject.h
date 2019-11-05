#pragma once
#include "Collision.h"
#include <map>
class GameObject
{
protected:
	float x, y;
	float width, height;
	float vx, vy;
public:
	GameObject();
	GameObject(float x, float y, float width, float height);
	virtual ~GameObject();

	virtual Box GetBoundingBox();

	virtual void Update(float deltaTime);
	void OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime);
	virtual void Draw();

	virtual D3DXVECTOR2 getPosition() 
	{
		return D3DXVECTOR2(x, y);
	}
};


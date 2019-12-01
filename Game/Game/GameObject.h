#pragma once
#include "Collision.h"
#include <map>
enum Tag {
	PlayerTag,
	GroundTag,
	PadTag,
	UnclassifiedTag,
	AppleTag,
	ItemTag,
	BulletAppleTag,
	PeddlerTag,
	ThinGuardTag,
	MustaheGuardTag
};

class GameObject
{
protected:
	// position init object
	float x, y;
	// size frame
	float width, height;
	// velocity
	float vx, vy;
	// status items
	
	bool m_isFacingRight = true;

	Tag m_tag; // object identification 
public:
	GameObject();
	GameObject(float x, float y, float width, float height, Tag tag);
	virtual ~GameObject();

	virtual Box GetBoundingBox();

	virtual void Update(float deltaTime);
	void OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime);
	virtual void Draw();

	virtual void setPosition(D3DXVECTOR2);
	virtual D3DXVECTOR2 getPosition() { return D3DXVECTOR2(x, y); }

	virtual Tag getTag() { return m_tag; }
	virtual float getWidth() { return width; }
	virtual float getHeight() { return height; }

	virtual D3DXVECTOR2 getVelocity() { return D3DXVECTOR2(vx, vy); }

	//top and bottom side, return y and y + height
	virtual float top() const;
	virtual float bottom() const;
	//left and right side, return x and x + width
	virtual float left() const;
	virtual float right() const;

	bool getIsFacingRight() const;
	void setIsFacingRight(bool value);
};


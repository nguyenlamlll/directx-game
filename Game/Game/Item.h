#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Sprite.h"
#include "Player.h"


enum ItemStatus
{
	NonActive,
	Active
};

class Item : public GameObject
{
protected:
	ItemStatus status;
	Animation* image;
	Player* m_player;
	// value check reset load animation
	DWORD last_time, start_wait;

	// has been die ? true = not die|| false = die (hidden object to do reset list object when player dead)
	bool isDead; 
	// has been used ? true = not used || false = used
	bool isUsed;
	bool isDied; 

public:
	//destructor of item class
	~Item();
	Item(float x, float y, float width, float height);
	Item(float x, float y, float width, float height, Tag tag);



	Box GetBoundingBox();

	D3DXVECTOR2 getVelocity();

	virtual void Update(float deltaTime);
	virtual void Draw();
	
	virtual void OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime);
	//action when item actived
	virtual void ActiveAction();
	virtual void NonActiveAction();

	void attachPlayer(Player* player);
	void OnInterSerct();


	//get status item
	int getStatus();

	
};

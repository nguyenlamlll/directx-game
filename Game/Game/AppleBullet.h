#pragma once
#include "Player.h"

enum Status {
	Fling,
	Burst,
};

class AppleBullet : public GameObject
{
protected:
	Status status;
	Animation* image;

	// has been deleted? true = not deleted || false = deleted (delete object in list)
	bool isDead; 
	// has been used ? true = not used || false = used
	bool isUsed; 
	// has been die ? true = not die|| false = die (hidden object to do reset list object when player dead)
	bool isDied; 

public:

	AppleBullet(float x, float y, float width, float height, Player* player);
	
	~AppleBullet();
	
	Box GetBoundingBox();

	D3DXVECTOR2 getVelocity();

	void Update(float deltaTime);
	void OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime);
	void Draw();

	void BurstAction();
};


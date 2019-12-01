#pragma once
#include "../Game/GameObject.h"
#include "../Game/Animation.h"
#include "../Game/Sprite.h"

enum PeddlerStatus
{
	NonActive,
	Active
};

enum PeddlerStates
{
	PeddlerTransform_1,
	PeddlerTransform_2,
	PeddlerTransform_3,
	PeddlerTransform_4,
};

class Peddler : public GameObject
{
protected:
	PeddlerStatus status;
	PeddlerStates state;

	Animation* image1;
	Animation* image2;
	// value check reset load animation
	DWORD last_time, start_wait;

	// has been die ? true = not die|| false = die (hidden object to do reset list object when player dead)
	bool isDead;
	// has been used ? true = not used || false = used
	bool isUsed;
	bool isDied;
public:
	Peddler(float x, float y, float width, float height);
	~Peddler();

	Box GetBoundingBox();

	D3DXVECTOR2 getVelocity();

	void Update(float deltaTime);
	void Draw();

	void OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime);
	//action when item actived
	void ActiveAction();
	void NonActiveAction();

	void changeState(PeddlerStates state);

	//
	void resetPeddler();
};

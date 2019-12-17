#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Sprite.h"
#include "Player.h"

enum class PeddlerStatus
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
	PeddlerStates m_state;

	Animation* m_image;
	Animation* m_imageTrf1;
	Animation* m_imageTrf2;
	Animation* m_imageTrf3;
	Animation* m_imageTrf4;
	Animation* m_imageStanding1;
	Animation* m_imageStanding2;


	Player* m_player;
	// value check reset load animation
	DWORD last_time, start_wait, start_waitStanding2;

	// has been die ? true = not die|| false = die (hidden object to do reset list object when player dead)
	bool isDead;
	// has been used ? true = not used || false = used
	bool isUsed;
	bool isDied;
	bool isTransform;
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

	void attachPlayer(Player* player);
	void OnInterSerct();
};

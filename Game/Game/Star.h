#pragma once
#include "Boss.h"
#include "Player.h"
#include "BulletBoss.h"

enum StarState {
	StarFling,
	StarHit
};
class Boss;

class Star : public BulletBoss
{
protected:
	StarState m_state;
	Animation* m_image;
	Animation* m_imageFling;
	Animation* m_imageHit;

	bool isDied;

	Player* m_player;
	Boss* m_boss;
	DWORD last_time;

public:
	Star(float x, float y, float width, float height, Boss* boss);
	~Star();

	Box GetBoundingBox();
	D3DXVECTOR2 getVelocity();
	void Update(float deltaTime);
	void Draw();

	void OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime);
	void OnCollision(GameObject* object, float deltaTime);

	void FlyingAction();
	void HitAction();
	void attachPlayer(Player* player);
	void OnInterSerct();
};

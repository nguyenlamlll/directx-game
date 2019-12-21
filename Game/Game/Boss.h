#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Player.h"
#include "Health.h"
#include <vector> 
#include "Star.h"
#include "Fire.h"

#include <unordered_map>

using namespace std;

enum BossState {
	WarlockStanding,
	WarlockMagicing,
	CobraRenascence,
	CobraAttack,
	BossDied
};

class Boss : public GameObject
{
protected:
	BossState m_state;

	// list object star and fire
	vector<BulletBoss*>list;

	Animation* m_image;
	Animation* m_image_WarlockStanding;
	Animation* m_image_WarlockMagicing;
	Animation* m_image_CobraRenascence;
	Animation* m_image_CobraAttack;
	Animation* m_image_BossDied;

	Animation* m_image_fire0;
	Animation* m_image_fire1;
	Animation* m_image_fire2;
	Animation* m_image_fire3;

	Health* m_health;

	Player* m_player;

	DWORD m_startWaitStanding, m_startWaitMagicing, m_startWaitAttack, m_WaitCreateStar, m_WaitCreateFire;

	bool isDead, isDied, isTransform, isCloseRange;

public:
	Boss(float x, float y, float width, float height, bool isFacingRight);
	~Boss();


	Box GetBoundingBox();
	D3DXVECTOR2 getVelocity();
	void Update(float deltaTime);
	void Draw();

	void OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime);
	void OnCollision(GameObject* colliableObject, float deltaTime);
	void attachPlayer(Player* player);
	void checkPositionWithPlayer();
	void checkHealthBoss();

	void WarlockStandingAction();
	void WarlockMagicingAction();
	void CobraRenascenceAction();
	void CobraAttackAction();
	void BossDiedAction();

	void createStar();
	void createFire();

	int randomPostionFire(bool type);
	void setPositionFire();

	void setPositionFireAladdin();

};

#pragma once
#include "GameObject.h"
#include "AppleBullet.h"
#include <vector> 
using namespace std;
enum PlayerStates {
	Standing,
	StandingLookAround,
	StandingThrow,
	Moving,
	MovingStop,
	MoveAttack,
	MoveThrow,
	SitDown,
	LookUp,
	StandAttack,
	StandAttackThrow,
	JumpStand,
	JumpMoving,
	JumpAttack,
	JumpAttackThrow,
	Falling,
	SitDownAttack,
	SitDownAttackThrow,
	PushWall,
	EndLevel,
	Climb,
	Swing,
	SwingStop,
	SwingAttack,
	SwingAttackThrow

};
class Player;
class PlayerState
{
protected:
	Player* m_player;
public:
	PlayerState() {}
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;
	virtual PlayerStates GetState() = 0;

	vector<AppleBullet*>* getListBullet();
	
	// PreCollision is called before the Update() function is called in the game loop.
	virtual void PreCollision(GameObject* entity, float deltaTime) = 0;

	// OnCollision is called after the Update() function is called in the game loop.
	virtual void OnCollision(GameObject* entity, float deltaTime) = 0;

	virtual void createAppleBullet() {};
	void deleteAppleBullet();
};


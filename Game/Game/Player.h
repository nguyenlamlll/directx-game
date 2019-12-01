#pragma once
#include "GameObject.h"
#include "Sprite.h";
#include "Input.h"
#include "Animation.h"

#include "PlayerState.h"
#include "PlayerStandingState.h"
#include "PlayerStandLookAround.h"
#include "PlayerStandThrowState.h"
#include "PlayerMovingState.h"
#include "PlayerMovingStopState.h"
#include "PlayerSitDownState.h"
#include "PlayerLookUpState.h"
#include "PlayerStandAttackState.h"
#include "PlayerStandAttackThrowState.h"
#include "PlayerFallingState.h"
#include "PlayerJumpAttackState.h"
#include "PlayerJumpStandState.h"
#include "PlayerJumpMovingState.h"
#include "PlayerJumpAttackThrowState.h"
#include "PlayerSitDownAttack.h"
#include "PlayerSitDownAttackThrowState.h"
#include "PlayerPushWallState.h"
#include "PlayerEndGameState.h"
#include "PlayerClimbState.h"
#include "PlayerSwingState.h"
#include "PlayerSwingStopState.h"
#include "PlayerSwingAttackState.h"
#include "PlayerSwingAttackThrowState.h"

#include <map>

class PlayerState;
class Player : public GameObject
{
public:
	D3DXVECTOR2 m_basePosition;

	ControlDevice m_controlDevice{ ControlDevice::Keyboard };
	float speed;

	Animation* m_currentAnimation;
	Animation* m_animationStand;
	Animation* m_animationStandLookAround;
	Animation* m_animationStandThrow;
	Animation* m_animationMoving;
	Animation* m_animationMovingStop;
	Animation* m_animationSitDown;
	Animation* m_animationLookUp;
	Animation* m_animationStandAttack;
	Animation* m_animationStandAttackThrow;
	Animation* m_animationJumpStand;
	Animation* m_animationJumpMoving;
	Animation* m_animationJumpAttack;
	Animation* m_animationJumpAttackThrow;
	Animation* m_animationFalling;
	Animation* m_animationSitDownAttack;
	Animation* m_animationSitDownAttackThrow;
	Animation* m_animationPushWall;
	Animation* m_animationEndGame;
	Animation* m_animationClimb;
	Animation* m_animationSwing;
	Animation* m_animationSwingStop;
	Animation* m_animationSwingAttack;
	Animation* m_animationSwingAttackThrow;

private:
	PlayerState* m_previousState;
	PlayerState* m_currentState;
public:
	PlayerState* getPreviousState();
	PlayerState* getCurrentState();

public:
	Player(float x, float y, float width, float height);
	~Player();

	Box GetBoundingBox();

	D3DXVECTOR2 getVelocity();

	void Update(float deltaTime);
	void OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime);
	void Draw();

	void changeState(PlayerStates state);
};


#pragma once
#include "GameObject.h"
#include "Sprite.h";
#include "Input.h"
#include "Animation.h"

#include "AppleBullet.h"

#include "PlayerState.h"
#include "PlayerStandingState.h"
#include "PlayerStandLookAround.h"
#include "PlayerStandThrowState.h"
#include "PlayerMovingState.h"
#include "PlayerMovingStopState.h"
#include "PlayerMoveAttackState.h"
#include "PlayerMoveThrowState.h"
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

#include "Health.h"

#include "Sound.h"
#include "SoundNames.h"

#include "ExitDoor.h"
#include "SceneManager.h"

#include <map>
class Camera;
class BossScene;
class PlayerState;
class AppleBullet;
class Player : public GameObject, public Health
{
private:
	DWORD start;
	// Used in flickering animation algorithm.
	int hurtCount{ 0 };
	bool m_isHurt{ false };
public:
	// Others call this function when attack Aladdin.
	// Aladdin will start running its own logic when being hurt (such as flickering animation).
	void isHit();

#if defined(DEBUG) | defined(_DEBUG)
public:
	bool m_isMovingFreely{ false };
#endif

public:
	bool m_canClimb{ false };
	bool m_isOnGround{ false };

	D3DXVECTOR2 m_basePosition;

	float speed;
	bool m_canMoveLeft{ true };
	bool m_canMoveRight{ true };

	Animation* m_currentAnimation;
	Animation* m_animationStand;
	Animation* m_animationStandLookAround;
	Animation* m_animationStandThrow;

	Animation* m_animationMoving;
	Animation* m_animationMovingStop;
	Animation* m_animationMoveAttack;
	Animation* m_animationMoveThrow;

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

private: 
	vector<AppleBullet*>lsAppleBullet;
public:
	void addAppleToList(AppleBullet*);

public:
	Player(float x, float y, float width, float height);
	~Player();

	Box GetBoundingBox();

	D3DXVECTOR2 getVelocity();
	void setVelocity(D3DXVECTOR2 value);

	void Update(float deltaTime);

	// PreCollision is called before the Update() function is called in the game loop.
	void PreCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime);

	// OnCollision is called after the Update() function is called in the game loop.
	void OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime);
	void Draw();

	void OncollisionWithApple(GameObject* obj, float deltaTime);
	void changeState(PlayerStates state);
};


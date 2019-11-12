#pragma once
#include "GameObject.h"
#include "Sprite.h";
#include "Input.h"
#include "Animation.h"

#include "PlayerState.h"
#include "PlayerStandingState.h"
#include "PlayerMovingState.h"

#include <map>

class PlayerState;
class Player : public GameObject
{
private:
	Sprite* m_playerSprite;
	ControlDevice m_controlDevice{ ControlDevice::Keyboard };
	float speed;

	Animation* m_currentAnimation;
	Animation* m_animationStand;
	Animation* m_animationJump;
	Animation* m_animationAttack;
	Animation* m_animationRun;

	PlayerState* m_currentState;
public:
	Player(float x, float y, float width, float height, LPCWSTR spritePath);
	~Player();

	void SetControlDevice(ControlDevice device);

	Box GetBoundingBox();

	D3DXVECTOR2 getVelocity();

	void Update(float deltaTime);
	void OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime);
	void Draw();

	void changeState(PlayerStates state);
};


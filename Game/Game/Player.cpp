#include "stdafx.h"
#include "Player.h"

Player::Player(float x, float y, float width, float height, LPCWSTR spritePath)
	: GameObject(x, y, width, height, Tag::PlayerTag)
{
	this->setPosition(D3DXVECTOR2(x,y));

	speed = 0.4f;

	m_animationStand = new Animation(L"Resources/animations/aladdin/Aladdin_Standing.png", 7, 1, 7, true, 100.f);
	m_animationStand->setPositionX(x);
	m_animationStand->setPositionY(y);
	m_animationJump = new Animation(L"Resources/animations/aladdin/Aladdin_Jumping.png", 10, 1, 10, true, 100.f);
	m_animationJump->setPositionX(x);
	m_animationJump->setPositionY(y);
	m_animationAttack = new Animation(L"Resources/animations/aladdin/Aladdin_Standing_Fight.png", 5, 1, 5, true, 100.f);
	m_animationAttack->setPositionX(x);
	m_animationAttack->setPositionY(y);
	m_animationRun = new Animation(L"Resources/animations/aladdin/Aladdin_Running.png", 13, 1, 13, true, 100.f);
	m_animationRun->setPositionX(x);
	m_animationRun->setPositionY(y);
	//m_currentAnimation = m_animationStand;

	changeState(PlayerStates::Moving);
}

Player::~Player()
{
	if (m_playerSprite) delete m_playerSprite;
}

void Player::SetControlDevice(ControlDevice device)
{
	m_controlDevice = device;
}

Box Player::GetBoundingBox()
{
	Box box;

	box.x = x;
	box.y = y;
	box.width = width;
	box.height = height;
	box.vx = vx;
	box.vy = vy;

	return box;
}

D3DXVECTOR2 Player::getVelocity()
{
	D3DXVECTOR2 result(vx, vy);
	return result;
}

void Player::Update(float deltaTime)
{
	//m_currentAnimation->Update(deltaTime);
	m_currentState->Update(deltaTime);

	if (KeyboardInput::GetInstance()->isKeyDown(VK_D)) {
		vx = speed * deltaTime;
		changeState(PlayerStates::Moving);
	}
	else if (KeyboardInput::GetInstance()->isKeyDown(VK_A)) {
		vx = -speed * deltaTime;
		changeState(PlayerStates::Moving);
	}
	else
	{
		vx = 0.0f;
	}


	if (KeyboardInput::GetInstance()->isKeyDown(VK_W)) {
		vy = -speed * deltaTime;
	}
	else if (KeyboardInput::GetInstance()->isKeyDown(VK_S)) {
		vy = speed * deltaTime;
	}
	else
	{
		vy = 0.0f;
	}

	if (KeyboardInput::GetInstance()->isKeyDown(VK_J)) {
		m_currentAnimation = m_animationAttack;
	}
	if (KeyboardInput::GetInstance()->isKeyDown(VK_K)) {
		m_currentAnimation = m_animationJump;
	}

	x = x + vx;
	y = y + vy;
	this->setPosition(D3DXVECTOR2(x, y));

	auto cameraOldPosition = Camera::getInstance()->getPosition();
	cameraOldPosition.x += vx;
	cameraOldPosition.y += vy;
	Camera::getInstance()->setPosition(cameraOldPosition);
	Camera::getInstance()->updateCamera(D3DXVECTOR2(x, y));
}

void Player::OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime)
{
	for (auto it = colliableObjects->begin(); it != colliableObjects->end(); it++)
	{
		float normalX, normalY;
		auto collisionResult = Collision::getInstance()->SweptAABB(this->GetBoundingBox(), it->second->GetBoundingBox(), normalX, normalY, deltaTime);
		if (collisionResult.isCollide)
		{
			vx = vy = 0;
			OutputDebugString(L"Player collide with something. \n");
		}
	}
}

void Player::Draw()
{
	//m_playerSprite->Draw();
	m_currentState->Draw();
}

void Player::changeState(PlayerStates state)
{
	if (m_currentState != nullptr)
		delete m_currentState;

	switch (state) {
	case PlayerStates::Jumping:
	{
		break;
	}
	case PlayerStates::Moving:
	{
		m_currentState = new PlayerMovingState(this, m_animationRun);
		break;
	}
	case PlayerStates::Standing:
	{
		m_currentState = new PlayerStandingState(this, m_animationStand);
		break;
	}
	}
}

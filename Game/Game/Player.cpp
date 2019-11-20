#include "stdafx.h"
#include "Player.h"

Player::Player(float x, float y, float width, float height, LPCWSTR spritePath)
	: GameObject(x, y, width, height, Tag::PlayerTag)
{
	this->setPosition(D3DXVECTOR2(x,y));

	speed = 0.4f;

	// Stand
	m_animationStand = new Animation(L"Resources/animations/aladdin/stand.png", 1, 1, 1);
	m_animationStand->setPositionX(x);
	m_animationStand->setPositionY(y);
	// Stand Look Around
	m_animationStandLookAround = new Animation(L"Resources/animations/aladdin/stand-look-around.png", 7, 1, 7, true, 100.f);
	m_animationStandLookAround->setPositionX(x);
	m_animationStandLookAround->setPositionY(y);
	// Stand Throw Apple
	m_animationStandThrow = new Animation(L"Resources/animations/aladdin/stand-throw.png", 12, 1, 12, true, 100.f);
	m_animationStandThrow->setPositionX(x);
	m_animationStandThrow->setPositionY(y);

	// Stand Attack
	m_animationStandAttack = new Animation(L"Resources/animations/aladdin/stand-attack.png", 5, 1, 5, true, 100.f);
	m_animationStandAttack->setPositionX(x);
	m_animationStandAttack->setPositionY(y);

	// Stand Attack Throw
	m_animationStandAttackThrow = new Animation(L"Resources/animations/aladdin/stand-attack-throw.png", 6, 1, 6, true, 100.f);
	m_animationStandAttackThrow->setPositionX(x);
	m_animationStandAttackThrow->setPositionY(y);

	// Moving
	m_animationMoving = new Animation(L"Resources/animations/aladdin/Aladdin_Running.png", 13, 1, 13, true, 70.f);
	m_animationMoving->setPositionX(x);
	m_animationMoving->setPositionY(y);

	//Moving Stop
	m_animationMovingStop = new Animation(L"Resources/animations/aladdin/moving-stop.png", 9, 1, 9, true, 100.f);
	m_animationMovingStop->setPositionX(x);
	m_animationMovingStop->setPositionY(y);
	// Sit Down
	m_animationSitDown = new Animation(L"Resources/animations/aladdin/sit-down.png", 4, 1, 4, true, 100.f);
	m_animationSitDown->setPositionX(x);
	m_animationSitDown->setPositionY(y);
	// Look up
	m_animationLookUp = new Animation(L"Resources/animations/aladdin/look-up.png", 3, 1, 3, true, 100.f);
	m_animationLookUp->setPositionX(x);
	m_animationLookUp->setPositionY(y);
	//Falling
	m_animationFalling = new Animation(L"Resources/animations/aladdin/falling.png", 4, 1, 4, true, 100.f);
	m_animationFalling->setPositionX(x);
	m_animationFalling->setPositionY(y);
	// Jump Attack
	m_animationJumpAttack = new Animation(L"Resources/animations/aladdin/jump-attack.png", 6, 1, 6, true, 100.f);
	m_animationJumpAttack->setPositionX(x);
	m_animationJumpAttack->setPositionY(y);
	// Jump Attack Throw
	m_animationJumpAttackThrow = new Animation(L"Resources/animations/aladdin/jump-attack-throw.png", 5, 1, 5, true, 100.f);
	m_animationJumpAttackThrow->setPositionX(x);
	m_animationJumpAttackThrow->setPositionY(y);
	// Jump Moving
	m_animationJumpMoving = new Animation(L"Resources/animations/aladdin/jump-moving.png", 6, 1, 6, true, 100.f);
	m_animationJumpMoving->setPositionX(x);
	m_animationJumpMoving->setPositionY(y);

	//Jump Stand
	m_animationJumpStand = new Animation(L"Resources/animations/aladdin/jump-stand.png", 5, 1, 5, true, 100.f);
	m_animationJumpStand->setPositionX(x);
	m_animationJumpStand->setPositionY(y);

	//Sit Down Attack
	m_animationSitDownAttack = new Animation(L"Resources/animations/aladdin/sit-down-attack.png", 7, 1, 7, true, 100.f);
	m_animationSitDownAttack->setPositionX(x);
	m_animationSitDownAttack->setPositionY(y);

	//Sit Down Attack Throw
	m_animationSitDownAttackThrow = new Animation(L"Resources/animations/aladdin/sit-down-attack-throw.png", 5, 1, 5, true, 100.f);
	m_animationSitDownAttackThrow->setPositionX(x);
	m_animationSitDownAttackThrow->setPositionY(y);

	// Push Wall
	 m_animationPushWall = new Animation(L"Resources/animations/aladdin/push-wall.png", 9, 1, 9, true, 100.f);
	 m_animationPushWall->setPositionX(x);
	 m_animationPushWall->setPositionY(y);

	 // End Game
	 m_animationEndGame = new Animation(L"Resources/animations/aladdin/end-level.png", 8, 1, 8, true, 100.f);
	 m_animationEndGame->setPositionX(x);
	 m_animationEndGame->setPositionY(y);

	 // Climb
	 m_animationClimb = new Animation(L"Resources/animations/aladdin/climb.png", 10, 1, 10, true, 100.f);
	 m_animationClimb->setPositionX(x);
	 m_animationClimb->setPositionY(y);

	 // Swing
	 m_animationSwing = new Animation(L"Resources/animations/aladdin/swing.png", 10, 1, 10, true, 100.f);
	 m_animationSwing->setPositionX(x);
	 m_animationSwing->setPositionY(y);

	 // Swing Stop
	 m_animationSwingStop = new Animation(L"Resources/animations/aladdin/swing-stop.png", 5, 1, 5, true, 100.f);
	 m_animationSwingStop->setPositionX(x);
	 m_animationSwingStop->setPositionY(y);

	 // Swing Attack
	 m_animationSwingAttack = new Animation(L"Resources/animations/aladdin/swing-attack.png", 7, 1, 7, true, 100.f);
	 m_animationSwingAttack->setPositionX(x);
	 m_animationSwingAttack->setPositionY(y);

	 // Swing Attack Throw
	 m_animationSwingAttackThrow = new Animation(L"Resources/animations/aladdin/swing-attack-throw.png", 5, 1, 5, true, 100.f);
	 m_animationSwingAttackThrow->setPositionX(x);
	 m_animationSwingAttackThrow->setPositionY(y);
	

	m_currentAnimation = m_animationStand;
	changeState(PlayerStates::Standing);
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
	m_currentState->Update(deltaTime);
	if (KeyboardInput::GetInstance()->isKeyTriggered(VK_D) || KeyboardInput::GetInstance()->isKeyTriggered(VK_A))
	{
		changeState(PlayerStates::Moving);
	}

	if (KeyboardInput::GetInstance()->isKeyDown(VK_D)) {
		vx = speed * deltaTime;
	}
	else if (KeyboardInput::GetInstance()->isKeyDown(VK_A)) {
		vx = -speed * deltaTime;
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

	/*if (KeyboardInput::GetInstance()->isKeyDown(VK_J)) {
		m_currentAnimation = m_animationAttack;
	}
	if (KeyboardInput::GetInstance()->isKeyDown(VK_K)) {
		m_currentAnimation = m_animationJump;
	}*/

	x = x + vx;
	y = y + vy;
	this->setPosition(D3DXVECTOR2(x, y));

	auto cameraOldPosition = Camera::getInstance()->getPosition();
	cameraOldPosition.x += vx;
	cameraOldPosition.y += vy;
	Camera::getInstance()->setPosition(cameraOldPosition);
	Camera::getInstance()->updateCamera(D3DXVECTOR2(x, y));

	m_currentAnimation->setPositionX(this->getPosition().x);
	m_currentAnimation->setPositionY(this->getPosition().y);
	m_currentAnimation->Update(deltaTime);
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
	m_currentAnimation->Draw();
}

void Player::changeState(PlayerStates state)
{
	if (m_currentState != nullptr)
		delete m_currentState;

	switch (state) {
	case PlayerStates::Moving:
	{
		m_currentState = new PlayerMovingState(this, m_animationMoving);
		m_currentAnimation = m_animationMoving;
		break;
	}
	case PlayerStates::MovingStop:
	{
		m_currentState = new PlayerMovingStopState(this, m_animationMovingStop);
		break;
	}
	case PlayerStates::Standing:
	{
		m_currentState = new PlayerStandingState(this, m_animationStand);
		m_currentAnimation = m_animationStand;
		break;
	}
	case PlayerStates::StandingLookAround: {
		m_currentState = new PlayerStandLookAround(this, m_animationStandLookAround);
		break;
	}
	case PlayerStates::StandingThrow: {
		m_currentState = new PlayerStandThrowState(this, m_animationStandThrow);
		break;
	}
	case PlayerStates::StandAttack: {
		m_currentState = new PlayerStandAttackState(this, m_animationStandAttack);
		break;
	}
	case PlayerStates::StandAttackThrow: {
		m_currentState = new PlayerStandAttackThrowState(this, m_animationStandAttackThrow);
		break;
	}
	case PlayerStates::SitDown: {
		m_currentState = new PlayerSitDownState(this, m_animationSitDown);
		break;
	}
	case PlayerStates::LookUp: {
		m_currentState = new PlayerLookUpState(this, m_animationLookUp);
		break;
	}
	case PlayerStates::Falling: {
		m_currentState = new PlayerLookUpState(this, m_animationFalling);
		break;
	}
	case PlayerStates::JumpAttack: {
		m_currentState = new PlayerJumpAttackState(this, m_animationJumpAttack);
		break;
	}
	case PlayerStates::JumpAttackThrow: {
		m_currentState = new PlayerJumpAttackThrowState(this, m_animationJumpAttackThrow);
		break;
	}
	case PlayerStates::JumpMoving: {
		m_currentState = new PlayerJumpMovingState(this, m_animationJumpMoving);
		break;
	}
	case PlayerStates::JumpStand: {
		m_currentState = new PlayerJumpStandSate(this, m_animationJumpStand);
		break;
	}
	case PlayerStates::SitDownAttack: {
		m_currentState = new PlayerSitDownAttack(this, m_animationSitDownAttack);
		break;
	}
	case PlayerStates::SitDownAttackThrow: {
		m_currentState = new PlayerSitDownAttackThrowState(this, m_animationSitDownAttackThrow);
		break;
	}
	case PlayerStates::PushWall: {
		m_currentState = new PlayerPushWallState(this, m_animationPushWall);
		break;
	}
	case PlayerStates::EndLevel: {
		m_currentState = new PlayerEndGameState(this, m_animationEndGame);
		break;
	}
	case PlayerStates::Climb: {
		m_currentState = new PlayerClimbState(this, m_animationClimb);
		break;
	}
	case PlayerStates::Swing: {
		m_currentState = new PlayerSwingState(this, m_animationSwing);
		break;
	}
	case PlayerStates::SwingStop: {
		m_currentState = new PlayerSwingStopState(this, m_animationSwingStop);
		break;
	}
	case PlayerStates::SwingAttack: {
		m_currentState = new PlayerSwingAttackState(this, m_animationSwingAttack);
		break;
	}
	case PlayerStates::SwingAttackThrow: {
		m_currentState = new PlayerSwingAttackThrowState(this, m_animationSwingAttackThrow);
		break;
	}
	}
}

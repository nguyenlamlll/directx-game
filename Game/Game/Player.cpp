#include "stdafx.h"
#include "Player.h"
#include "Camera.h"
#include "BossScene.h"

void Player::isHit()
{
	m_isHurt = true;
	Sound::getInstance()->play(SoundNames::ALADDIN_HURT_SOUND, false);
}

PlayerState * Player::getPreviousState()
{
	return m_previousState;
}

PlayerState* Player::getCurrentState()
{
	return m_currentState;
}

void Player::addAppleToList(AppleBullet* bullet)
{
	lsAppleBullet.push_back(bullet);
	m_appleCount -= 1;
}

Player::Player(float x, float y, float width, float height)
	: GameObject(x, y, width, height, Tag::PlayerTag), Health(9)
{
	m_basePosition = D3DXVECTOR2(x, y);
	this->setPosition(m_basePosition);
	speed = 0.2f;
	vx = vy = 0;

	// Stand
	m_animationStand = new Animation(L"Resources/animations/aladdin/stand.png", 1, 1, 1);
	// Stand Look Around
	m_animationStandLookAround = new Animation(L"Resources/animations/aladdin/stand-look-around.png", 7, 1, 7, true, 150.f);
	// Stand Throw Apple
	m_animationStandThrow = new Animation(L"Resources/animations/aladdin/stand-throw.png", 12, 1, 12, true, 40.f);
	// Stand Attack
	m_animationStandAttack = new Animation(L"Resources/animations/aladdin/stand-attack.png", 5, 1, 5, false, 20.f);
	// Stand Attack Throw
	m_animationStandAttackThrow = new Animation(L"Resources/animations/aladdin/stand-attack-throw.png", 6, 1, 6, false, 60.f);

	// Moving
	m_animationMoving = new Animation(L"Resources/animations/aladdin/Aladdin_Running.png", 13, 1, 13, true, 60.f);
	//Moving Stop
	m_animationMovingStop = new Animation(L"Resources/animations/aladdin/moving-stop.png", 9, 1, 9, true, 100.f);
	// Move and Attack
	m_animationMoveAttack = new Animation(L"Resources/animations/aladdin/move-attack.png", 6, 1, 6, false, 20.f, D3DCOLOR_XRGB(106, 148, 189));
	// Move and Throw
	m_animationMoveThrow = new Animation(L"Resources/animations/aladdin/move-throw.png", 6, 1, 6, false, 60.f, D3DCOLOR_XRGB(106, 148, 189));

	// Sit Down
	m_animationSitDown = new Animation(L"Resources/animations/aladdin/sit-down.png", 4, 1, 4, false, 30.f);
	//Sit Down Attack
	m_animationSitDownAttack = new Animation(L"Resources/animations/aladdin/sit-down-attack.png", 7, 1, 7, false, 20.f);
	//Sit Down Attack Throw
	m_animationSitDownAttackThrow = new Animation(L"Resources/animations/aladdin/sit-down-attack-throw.png", 5, 1, 5, false, 60.f);

	// Look up
	m_animationLookUp = new Animation(L"Resources/animations/aladdin/look-up.png", 3, 1, 3, false, 100.f);

	//Falling
	m_animationFalling = new Animation(L"Resources/animations/aladdin/falling.png", 4, 1, 4, true, 100.f);

	// Jump Attack
	m_animationJumpAttack = new Animation(L"Resources/animations/aladdin/jump-attack.png", 6, 1, 6, false, 40.f);
	// Jump Attack Throw
	m_animationJumpAttackThrow = new Animation(L"Resources/animations/aladdin/jump-attack-throw.png", 5, 1, 5, false, 60.f);
	// Jump Moving
	m_animationJumpMoving = new Animation(L"Resources/animations/aladdin/jump-moving.png", 6, 1, 6, true, 100.f);
	//Jump Stand
	m_animationJumpStand = new Animation(L"Resources/animations/aladdin/jump-stand.png", 5, 1, 5, true, 100.f);

	// Push Wall
	m_animationPushWall = new Animation(L"Resources/animations/aladdin/push-wall.png", 9, 1, 9, true, 100.f);

	// End Game
	m_animationEndGame = new Animation(L"Resources/animations/aladdin/end-level.png", 8, 1, 8, true, 100.f);

	// Climb
	m_animationClimb = new Animation(L"Resources/animations/aladdin/climb.png", 10, 1, 10, true, 60.f);
	m_animationClimbAttack = new Animation(L"Resources/AladdinState/PNG/AladdinClimbAttack_7.png", 7, 1, 7, false, 40.f);
	m_animationClimbThrow = new Animation(L"Resources/AladdinState/PNG/AladdinClimbAttackThrow_5.png", 5, 1, 5, false, 40.f);
	m_animationClimbJump = new Animation(L"Resources/AladdinState/PNG/AladdinClimbJumb_9.png", 9, 1, 9, true, 40.f);

	// Swing
	m_animationSwing = new Animation(L"Resources/animations/aladdin/swing.png", 10, 1, 10, true, 100.f);
	// Swing Stop
	m_animationSwingStop = new Animation(L"Resources/animations/aladdin/swing-stop.png", 5, 1, 5, true, 100.f);
	// Swing Attack
	m_animationSwingAttack = new Animation(L"Resources/animations/aladdin/swing-attack.png", 7, 1, 7, true, 100.f);
	// Swing Attack Throw
	m_animationSwingAttackThrow = new Animation(L"Resources/animations/aladdin/swing-attack-throw.png", 5, 1, 5, true, 60.f);

	m_currentAnimation = m_animationStand;
	changeState(PlayerStates::Standing);

	start = GetTickCount();
}

Player::~Player()
{
	delete m_animationStand;
	delete m_animationStandLookAround;
	delete m_animationStandThrow;
	delete m_animationStandAttack;
	delete m_animationStandAttackThrow;

	delete m_animationMoving;
	delete m_animationMovingStop;
	delete m_animationMoveAttack;

	delete m_animationSitDown;
	delete m_animationSitDownAttack;
	delete m_animationSitDownAttackThrow;
	delete m_animationLookUp;
	delete m_animationFalling;
	delete m_animationJumpAttack;
	delete m_animationJumpAttackThrow;
	delete m_animationJumpMoving;
	delete m_animationJumpStand;
	delete m_animationPushWall;
	delete m_animationEndGame;

	delete m_animationClimb;
	delete m_animationClimbAttack;
	delete m_animationClimbThrow;
	delete m_animationClimbJump;

	delete m_animationSwing;
	delete m_animationSwingStop;
	delete m_animationSwingAttack;
	delete m_animationSwingAttackThrow;

	delete m_currentState;
	delete m_previousState;
}

Box Player::GetBoundingBox()
{
	Box box;

	box.x = x - width / 2;
	box.y = y - height / 2;
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

void Player::setVelocity(D3DXVECTOR2 value)
{
	vx = value.x;
	vy = value.y;
}

void Player::Update(float deltaTime)
{
#if defined(DEBUG) | defined(_DEBUG)
	if (KeyboardInput::GetInstance()->isKeyTriggered(VK_F2))
	{
		m_isMovingFreely = !m_isMovingFreely;
	}
#endif

	auto now = GetTickCount();
	auto dt = now - start;
	if (dt > 3000)
	{
		m_isHurt = false;
		start = GetTickCount();
	}

	m_currentState->Update(deltaTime);

	if (lsAppleBullet.size() != 0) {
		for (int j = 0; j < lsAppleBullet.size(); j++) {
			if (!lsAppleBullet.at(j)->getIsDead())
				lsAppleBullet.at(j)->Update(deltaTime);
			else {
				delete lsAppleBullet.at(j);
				lsAppleBullet.at(j) = nullptr;
				lsAppleBullet.erase(lsAppleBullet.begin() + j);
			}
		}
	}

	if (KeyboardInput::GetInstance()->isKeyDown(VK_D))
	{
		this->setIsFacingRight(true);

		if (m_currentState->GetState() == PlayerStates::Standing ||
			m_currentState->GetState() == PlayerStates::Moving ||
			m_currentState->GetState() == PlayerStates::MoveAttack ||
			m_currentState->GetState() == PlayerStates::MoveThrow ||
			m_currentState->GetState() == PlayerStates::JumpStand ||
			m_currentState->GetState() == PlayerStates::JumpMoving ||
			m_currentState->GetState() == PlayerStates::JumpAttack ||
			m_currentState->GetState() == PlayerStates::JumpAttackThrow ||
			// m_currentState->GetState() == PlayerStates::Climb ||
			m_currentState->GetState() == PlayerStates::ClimbJump)

		{
			if (m_canMoveRight)
			{
				vx = speed * deltaTime;
			}
			else
			{
				vx = 0.0f;
			}
		}
	}
	else if (KeyboardInput::GetInstance()->isKeyDown(VK_A))
	{
		this->setIsFacingRight(false);

		if (m_currentState->GetState() == PlayerStates::Standing ||
			m_currentState->GetState() == PlayerStates::Moving ||
			m_currentState->GetState() == PlayerStates::MoveAttack ||
			m_currentState->GetState() == PlayerStates::MoveThrow ||
			m_currentState->GetState() == PlayerStates::JumpStand ||
			m_currentState->GetState() == PlayerStates::JumpMoving ||
			m_currentState->GetState() == PlayerStates::JumpAttack ||
			m_currentState->GetState() == PlayerStates::JumpAttackThrow ||
			// m_currentState->GetState() == PlayerStates::Climb ||
			m_currentState->GetState() == PlayerStates::ClimbJump)
		{
			if (m_canMoveLeft)
			{
				vx = -speed * deltaTime;
			}
			else
			{
				vx = 0.0f;
			}
		}
	}
	else
	{
		vx = 0.0f;
	}
	if (KeyboardInput::GetInstance()->isKeyDown(VK_A) && KeyboardInput::GetInstance()->isKeyDown(VK_D))
	{
		vx = 0.0f;
	}

	if (KeyboardInput::GetInstance()->isKeyDown(VK_W) && (m_currentState->GetState() == PlayerStates::Climb))
	{
		vy = -speed * deltaTime;
	}
	else if (KeyboardInput::GetInstance()->isKeyDown(VK_S) && (m_currentState->GetState() == PlayerStates::Climb))
	{
		vy = speed * deltaTime;
	}
	else
	{
		vy = 0.0f;
	}

#if defined(DEBUG) | defined(_DEBUG)
	if (m_isMovingFreely)
	{
		if (KeyboardInput::GetInstance()->isKeyDown(VK_W))
		{
			vy = -speed * deltaTime;
		}
		else if (KeyboardInput::GetInstance()->isKeyDown(VK_S))
		{
			vy = speed * deltaTime;
		}
	}
#endif


	x = x + vx;
	y = y + vy;
	this->setPosition(D3DXVECTOR2(x, y));

	auto cameraOldPosition = Camera::getInstance()->getPosition();
	cameraOldPosition.x += vx;
	cameraOldPosition.y += vy;
	Camera::getInstance()->setPosition(cameraOldPosition);
	Camera::getInstance()->updateCamera();
}

void Player::PreCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime)
{

	for (auto it = colliableObjects->begin(); it != colliableObjects->end(); it++)
	{
		auto entity = it->second;
		if (entity->getTag() == Tag::VerticleWallTag)
		{
			float normalX, normalY;
			auto result = Collision::getInstance()->SweptAABB(this->GetBoundingBox(), dynamic_cast<VerticalWall*>(entity)->GetBoundingBox(), normalX, normalY, deltaTime);
			if (result.isCollide)
			{
				if (result.sideCollided == CollisionSide::Right)
				{
					OutputDebugString(L"[INFO] Player is about to collide with Vertical Wall on the left side of the player. \n");
					this->m_canMoveLeft = false;
					this->m_canMoveRight = true;
				}
				if (result.sideCollided == CollisionSide::Left)
				{
					OutputDebugString(L"[INFO] Player is about to collide with Vertical Wall on the right side of the player. \n");
					this->m_canMoveLeft = true;
					this->m_canMoveRight = false;
				}
			}
			else
			{
				if (Collision::getInstance()->isColliding(this->GetBoundingBox(), dynamic_cast<VerticalWall*>(entity)->GetBoundingBox()))
				{
					OutputDebugString(L"[INFO] Player is colliding with Vertical Wall. \n");
					this->m_canMoveLeft = false;
					this->m_canMoveRight = false;

					if (dynamic_cast<VerticalWall*>(entity)->left() < this->left())
					{
						this->m_canMoveLeft = false;
						this->m_canMoveRight = true;
					}
					if (this->right() <= dynamic_cast<VerticalWall*>(entity)->getPosition().x)
					{
						this->m_canMoveLeft = true;
						this->m_canMoveRight = false;
					}
				}
			}

		}

		m_currentState->PreCollision(it->second, deltaTime);
	}
}

void Player::OncollisionWithApple(GameObject* obj, float deltaTime)
{
	if (lsAppleBullet.size() != 0) {
		for (int j = 0; j < lsAppleBullet.size(); j++) {
			if (!lsAppleBullet.at(j)->getIsDead()) {
				lsAppleBullet.at(j)->OnCollision(obj, deltaTime);
			}
		}
	}
}


void Player::OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime)
{
#if defined(DEBUG) | defined(_DEBUG)
	if (m_isMovingFreely)
	{
		// Leave empty
	}
	else {
		m_isOnGround = false;
	}
#else
	m_isOnGround = false;
#endif
	for (auto it = colliableObjects->begin(); it != colliableObjects->end(); it++)
	{
		m_currentState->OnCollision(it->second, deltaTime);
		this->OncollisionWithApple(it->second, deltaTime);

		auto entity = it->second;
		if (entity->getTag() == Tag::SpikeTag)
		{
			auto spike = dynamic_cast<Spike*>(entity);
			if (Collision::getInstance()->isColliding(this->GetBoundingBox(), spike->GetBoundingBox()))
			{
				if (spike->m_isAttackingHit == false &&
					spike->getStatus() == _StatusDamage::Damage)
				{
					spike->m_isAttackingHit = true;
					this->isHit();
					m_currentHealth -= 0.5;
				}
			}
		}
		if (entity->getTag() == Tag::HangingMorningStarTag)
		{
			auto morningStar = dynamic_cast<HangingMorningStar*>(entity);
			if (Collision::getInstance()->isColliding(this->GetBoundingBox(), morningStar->GetBoundingBox()))
			{
				if (morningStar->m_isAttackingHit == false &&
					morningStar->getStatus() == _StatusDamage::Damage)
				{
					morningStar->m_isAttackingHit = true;
					this->isHit();
					m_currentHealth -= 0.5;
				}
			}
		}
	}
	}

void Player::Draw()
{
	if (lsAppleBullet.size() != 0) {
		for (int j = 0; j < lsAppleBullet.size(); j++) {
			if (!lsAppleBullet.at(j)->getIsDead())
				lsAppleBullet.at(j)->Draw();
		}
	}
	if (m_isHurt)
	{
		// Begin the flickering process. A cycle contains 3 frames: { 0, 1, 2 }
		// where frame 0 draws the player. 1 and 2 don't. 
		if (hurtCount == 0)
		{
			m_currentState->Draw();
		}
		hurtCount++;
		if (hurtCount == 3)
		{
			hurtCount = 0;
		}

	}
	else
	{
		m_currentState->Draw();
	}
}

// This method should be call at the end of an update loop. 
// Because it will delete the running state and replace with a new one.
void Player::changeState(PlayerStates state)
{
	m_isOnGround = false;
	if (m_currentState != nullptr)
	{
		if (m_previousState != nullptr)
		{
			delete m_previousState;
		}
		m_previousState = m_currentState;
	}

	PlayerState* newState = nullptr;
	switch (state) {
	case PlayerStates::Moving:
	{
		newState = new PlayerMovingState(this, m_animationMoving);
		break;
	}
	case PlayerStates::MoveAttack:
	{
		newState = new PlayerMoveAttackState(this, m_animationMoveAttack);
		break;
	}
	case PlayerStates::MoveThrow:
	{
		newState = new PlayerMoveThrowState(this, m_animationMoveThrow);
		break;
	}
	case PlayerStates::MovingStop:
	{
		newState = new PlayerMovingStopState(this, m_animationMovingStop);
		break;
	}
	case PlayerStates::Standing:
	{
		newState = new PlayerStandingState(this, m_animationStand, m_animationStandLookAround);
		break;
	}
	case PlayerStates::StandingLookAround: {
		newState = new PlayerStandLookAround(this, m_animationStandLookAround);
		break;
	}
	case PlayerStates::StandingThrow: {
		newState = new PlayerStandThrowState(this, m_animationStandThrow);
		break;
	}
	case PlayerStates::StandAttack: {
		newState = new PlayerStandAttackState(this, m_animationStandAttack);
		break;
	}
	case PlayerStates::StandAttackThrow: {
		newState = new PlayerStandAttackThrowState(this, m_animationStandAttackThrow);
		break;
	}
	case PlayerStates::SitDown: {
		newState = new PlayerSitDownState(this, m_animationSitDown, false);
		break;
	}
	case PlayerStates::LookUp: {
		newState = new PlayerLookUpState(this, m_animationLookUp);
		break;
	}
	case PlayerStates::Falling: {
		newState = new PlayerLookUpState(this, m_animationFalling);
		break;
	}
	case PlayerStates::JumpAttack: {
		newState = new PlayerJumpAttackState(this, m_animationJumpAttack);
		break;
	}
	case PlayerStates::JumpAttackThrow: {
		newState = new PlayerJumpAttackThrowState(this, m_animationJumpAttackThrow);
		break;
	}
	case PlayerStates::JumpMoving: {
		newState = new PlayerJumpMovingState(this, m_animationJumpMoving);
		break;
	}
	case PlayerStates::JumpStand: {
		newState = new PlayerJumpStandState(this, m_animationJumpStand);
		break;
	}
	case PlayerStates::SitDownAttack: {
		newState = new PlayerSitDownAttack(this, m_animationSitDownAttack);
		break;
	}
	case PlayerStates::SitDownAttackThrow: {
		newState = new PlayerSitDownAttackThrowState(this, m_animationSitDownAttackThrow);
		break;
	}
	case PlayerStates::PushWall: {
		newState = new PlayerPushWallState(this, m_animationPushWall);
		break;
	}
	case PlayerStates::EndLevel: {
		//newState = new PlayerEndGameState(this, m_animationEndGame);
		break;
	}
	case PlayerStates::Climb: {
		newState = new PlayerClimbState(this, m_animationClimb);
		break;
	}
	case PlayerStates::ClimbAttack: {
		newState = new PlayerClimbAttackState(this, m_animationClimbAttack);
		break;
	}
	case PlayerStates::ClimbThrow: {
		newState = new PlayerClimbThrowState(this, m_animationClimbThrow);
		break;
	}
	case PlayerStates::ClimbJump: {
		newState = new PlayerClimbJumpState(this, m_animationClimbJump);
		break;
	}
	case PlayerStates::Swing: {
		//newState = new PlayerSwingState(this, m_animationSwing);
		break;
	}
	case PlayerStates::SwingStop: {
		//newState = new PlayerSwingStopState(this, m_animationSwingStop);
		break;
	}
	case PlayerStates::SwingAttack: {
		//newState = new PlayerSwingAttackState(this, m_animationSwingAttack);
		break;
	}
	case PlayerStates::SwingAttackThrow: {
		//newState = new PlayerSwingAttackThrowState(this, m_animationSwingAttackThrow);
		break;
	}
	default: {
		break;
	}
	}
	m_currentState = newState;
}

#include "stdafx.h"
#include "ThinGuard.h"

ThinGuard::ThinGuard(float x, float y, float width, float height)
	: GameObject(x, y, width, height, Tag::ThinGuardTag), Health(15)
{
	m_initialPosition = D3DXVECTOR2(x, y);
	this->setPosition(m_initialPosition);

	m_animations[ThinGuardStates::Standing] = new Animation(L"Resources/animations/enemy/thin-guard/stand.png", 1, 1, 1, true, 100.f, D3DCOLOR_XRGB(120, 193, 152));
	m_animations[ThinGuardStates::Standing]->setPositionX(x);
	m_animations[ThinGuardStates::Standing]->setPositionY(y);

	m_animations[ThinGuardStates::Moving] = new Animation(L"Resources/animations/enemy/thin-guard/move.png", 8, 1, 8, true, 75.f, D3DCOLOR_XRGB(120, 193, 152));
	m_animations[ThinGuardStates::Moving]->setPositionX(x);
	m_animations[ThinGuardStates::Moving]->setPositionY(y);

	m_animations[ThinGuardStates::Attacking] = new Animation(L"Resources/animations/enemy/thin-guard/attack.png", 6, 1, 6, false, 80.f, D3DCOLOR_XRGB(120, 193, 152));
	m_animations[ThinGuardStates::Attacking]->setPositionX(x);
	m_animations[ThinGuardStates::Attacking]->setPositionY(y);

	m_animations[ThinGuardStates::BeingHit] = new Animation(L"Resources/animations/enemy/thin-guard/being-hit.png", 9, 1, 9, false, 80.f, D3DCOLOR_XRGB(120, 193, 152));
	m_animations[ThinGuardStates::BeingHit]->setPositionX(x);
	m_animations[ThinGuardStates::BeingHit]->setPositionY(y);

	isDead = false;
	m_animations[ThinGuardStates::ThinBurst] = new Animation(L"Resources/Enmity/PNG/burst-bat_88_56_8.png", 8, 1, 8, false, 60.f);
	m_animations[ThinGuardStates::ThinBurst]->setPositionX(x);
	m_animations[ThinGuardStates::ThinBurst]->setPositionY(y);

	m_currentState = ThinGuardStates::Standing;
	m_currentAnimation = m_animations[ThinGuardStates::Standing];
}


ThinGuard::~ThinGuard()
{
	delete m_animations[ThinGuardStates::Standing];
	delete m_animations[ThinGuardStates::Moving];
	delete m_animations[ThinGuardStates::Attacking];
	delete m_animations[ThinGuardStates::BeingHit];
}

void ThinGuard::attachPlayer(Player * player)
{
	m_player = player;
}

void ThinGuard::checkPositionWithPlayer()
{
	float distance = MathHelper::findDistance(m_player->getPosition(), this->getPosition());
	if (distance <= m_attackRange)
	{
		m_currentState = ThinGuardStates::Attacking;
		m_currentAnimation = m_animations[ThinGuardStates::Attacking];
	}
	else
	{
		if (distance <= m_moveRange)
		{
			if (m_player->getPosition().x < (m_initialPosition.x - m_moveRange) ||
				(m_player->getPosition().x > (m_initialPosition.x + m_moveRange)))
			{
				m_currentState = ThinGuardStates::Standing;
				m_currentAnimation = m_animations[ThinGuardStates::Standing];
			}
			else
			{
				m_currentState = ThinGuardStates::Moving;
				m_currentAnimation = m_animations[ThinGuardStates::Moving];
			}
		}
		else
		{
			m_currentState = ThinGuardStates::Standing;
			m_currentAnimation = m_animations[ThinGuardStates::Standing];
		}
	}
}

void ThinGuard::isHit()
{
	m_isBeingHit = true;
	Sound::getInstance()->play(SoundNames::GUARD_HIT_2_SOUND, false);
}

Box ThinGuard::GetBoundingBox()
{
	Box box;

	box.x = x - width / 2;
	box.y = y - height / 2;
	box.width = width + 50;
	box.height = height + 50;
	box.vx = vx;
	box.vy = vy;

	return box;
}

Box ThinGuard::GetBoundingBoxForApple()
{
	Box box;
	switch (m_currentState)
	{
	case ThinGuardStates::Standing:
		box.x = x;
		box.y = y + 5;
		box.width = 45;
		box.height = 60;
		box.vx = vx;
		box.vy = vy;
		break;
	case ThinGuardStates::Moving:
		box.x = x;
		box.y = y;
		box.width = 45;
		box.height = 70;
		box.vx = vx;
		box.vy = vy;
		break;
	case ThinGuardStates::Attacking: case ThinGuardStates::BeingHit:
		box.x = x;
		box.y = y + 7;
		box.width = 40;
		box.height = 60;
		box.vx = vx;
		box.vy = vy;
		break;
	case ThinGuardStates::ThinBurst:
		box.x = x;
		box.y = y;
		box.width = 0;
		box.height = 0;
		box.vx = vx;
		box.vy = vy;
		break;
	default:
		box.x = x;
		box.y = y;
		box.width = 0;
		box.height = 0;
		box.vx = vx;
		box.vy = vy;
		break;
	}
	return box;
}

void ThinGuard::Update(float deltaTime)
{
	if (m_currentHealth > 0.0f)
	{
		checkPositionWithPlayer();
		if (m_isBeingHit)
		{
			if (m_animations[ThinGuardStates::BeingHit]->getIsFinished() == false)
			{
				m_currentState = ThinGuardStates::BeingHit;
				m_currentAnimation = m_animations[ThinGuardStates::BeingHit];
				checkAndUpdateDirection();
				m_currentAnimation->setPositionX(x);
				m_currentAnimation->setPositionY(y);
			}
			else
			{
				m_isBeingHit = false;
				m_animations[ThinGuardStates::BeingHit]->Reset();
			}

		}
		switch (m_currentState)
		{
		case (ThinGuardStates::Standing):
		{
			checkAndUpdateDirection();
			m_currentAnimation->setPositionX(x);
			m_currentAnimation->setPositionY(y);
			break;
		}
		case (ThinGuardStates::Attacking):
		{
			checkAndUpdateDirection();
			m_currentAnimation->setPositionX(x);
			m_currentAnimation->setPositionY(y);
			if (m_currentAnimation->getIsFinished() == true)
			{
				m_isAttackingHit = false;
				m_currentAnimation->Reset();
			}
			break;
		}
		case (ThinGuardStates::Moving):
		{
			D3DXVECTOR2 newPosition;
			if (isPlayerOnTheLeft())
			{
				newPosition = D3DXVECTOR2(x - speed * deltaTime, y);
			}
			else
			{
				newPosition = D3DXVECTOR2(x + speed * deltaTime, y);
			}

			this->setPosition(newPosition);
			checkAndUpdateDirection();
			m_currentAnimation->setPositionX(x);
			m_currentAnimation->setPositionY(y);
			break;
		}
		}
		m_currentAnimation->Update(deltaTime);
	}
	else {
		if (!isDead) {
			m_currentState = ThinGuardStates::ThinBurst;
			m_currentAnimation = m_animations[ThinGuardStates::ThinBurst];
			m_currentAnimation->setPositionX(x);
			m_currentAnimation->setPositionY(y);
			if (m_currentAnimation->getIsFinished())
				isDead = true;
			m_currentAnimation->Update(deltaTime);
		}
	}
}

void ThinGuard::checkAndUpdateDirection()
{
	if (isPlayerOnTheLeft())
	{
		m_currentAnimation->setFlipHorizontal(false);
	}
	else
	{
		m_currentAnimation->setFlipHorizontal(true);
	}
}

bool ThinGuard::isPlayerOnTheLeft()
{
	if (m_player->getPosition().x < this->x)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void ThinGuard::OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime)
{
}

void ThinGuard::OnCollision(GameObject* colliableObject, float deltaTime)
{
	if (colliableObject->getTag() == PlayerTag) {
		auto player = dynamic_cast<Player*>(colliableObject);
		auto self = this->GetBoundingBox();
		self.x -= 30;
		self.y -= 30;
		if (Collision::getInstance()->isColliding(self, player->GetBoundingBox()))
		{
			if (m_isAttackingHit == false && player->getCurrentHealth() > 0.0f)
			{
				OutputDebugString(L"[INFO] ThinGuard attacks Player.\n");
				player->takeDamage(0.5);
				player->isHit();
				m_isAttackingHit = true;
			}
		}
	}
	if (colliableObject->getTag()== BulletAppleTag) {
		takeDamage(0.5);
		if (m_currentHealth > 0)
			m_isBeingHit = true;
	}	
}

void ThinGuard::Draw()
{
	if (m_currentHealth > 0.0f)
	{
		m_currentAnimation->Draw();
	} else {
		if (!isDead)
			m_currentAnimation->Draw();
	}
}

void ThinGuard::setAttackRange(int value)
{
	m_attackRange = value;
}

void ThinGuard::setMoveRange(int value)
{
	m_moveRange = value;
}

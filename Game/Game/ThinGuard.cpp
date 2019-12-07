#include "stdafx.h"
#include "ThinGuard.h"

constexpr auto ATTACK_RANGE = 90;
constexpr auto MOVE_RANGE = 200;

ThinGuard::ThinGuard(float x, float y, float width, float height)
	: GameObject(x, y, width, height, Tag::ThinGuardTag), Health(20)
{
	m_initialPosition = D3DXVECTOR2(x, y);
	this->setPosition(m_initialPosition);

	m_animations[ThinGuardStates::Standing] = new Animation(L"Resources/animations/enemy/thin-guard/stand.png", 1, 1, 1, true, 100.f, D3DCOLOR_XRGB(120, 193, 152));
	m_animations[ThinGuardStates::Standing]->setPositionX(x);
	m_animations[ThinGuardStates::Standing]->setPositionY(y);

	m_animations[ThinGuardStates::Moving] = new Animation(L"Resources/animations/enemy/thin-guard/move.png", 8, 1, 8, true, 75.f, D3DCOLOR_XRGB(120, 193, 152));
	m_animations[ThinGuardStates::Moving]->setPositionX(x);
	m_animations[ThinGuardStates::Moving]->setPositionY(y);

	m_animations[ThinGuardStates::Attacking] = new Animation(L"Resources/animations/enemy/thin-guard/attack.png", 6, 1, 6, true, 80.f, D3DCOLOR_XRGB(120, 193, 152));
	m_animations[ThinGuardStates::Attacking]->setPositionX(x);
	m_animations[ThinGuardStates::Attacking]->setPositionY(y);

	m_animations[ThinGuardStates::BeingHit] = new Animation(L"Resources/animations/enemy/thin-guard/being-hit.png", 9, 1, 9, true, 80.f, D3DCOLOR_XRGB(120, 193, 152));
	m_animations[ThinGuardStates::BeingHit]->setPositionX(x);
	m_animations[ThinGuardStates::BeingHit]->setPositionY(y);

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
	if (distance <= ATTACK_RANGE)
	{
		m_currentState = ThinGuardStates::Attacking;
		m_currentAnimation = m_animations[ThinGuardStates::Attacking];
	}
	else
	{
		if (distance <= MOVE_RANGE)
		{
			if (m_player->getPosition().x < (m_initialPosition.x - MOVE_RANGE) ||
				(m_player->getPosition().x > (m_initialPosition.x + MOVE_RANGE)))
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
}

Box ThinGuard::GetBoundingBox()
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

void ThinGuard::Draw()
{
	if (m_currentHealth > 0.0f)
	{
		m_currentAnimation->Draw();
	}
}

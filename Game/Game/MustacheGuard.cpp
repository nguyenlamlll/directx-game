#include "stdafx.h"
#include "MustacheGuard.h"

constexpr auto ATTACK_RANGE = 90;
constexpr auto MOVE_RANGE = 200;
constexpr auto ATTACKING1_SPRITE_OFFSET = 12;
constexpr auto BEING_HIT_SPRITE_OFFSET = 12;

MustacheGuard::MustacheGuard(float x, float y, float width, float height)
	: GameObject(x, y, width, height, Tag::MustaheGuardTag), Health(15)
{
	m_initialPosition = D3DXVECTOR2(x, y);
	this->setPosition(m_initialPosition);

	m_animations[MustacheGuardStates::Standing] = new Animation(L"Resources/animations/enemy/mustache-guard/mock.png", 6, 1, 6, true, 90.f, D3DCOLOR_XRGB(120, 193, 152));
	m_animations[MustacheGuardStates::Standing]->setPositionX(x);
	m_animations[MustacheGuardStates::Standing]->setPositionY(y);

	m_animations[MustacheGuardStates::Attacking1] = new Animation(L"Resources/animations/enemy/mustache-guard/attack-1.png", 5, 1, 5, false, 80.f, D3DCOLOR_XRGB(120, 193, 152));
	m_animations[MustacheGuardStates::Attacking1]->setPositionX(x);
	m_animations[MustacheGuardStates::Attacking1]->setPositionY(y - ATTACKING1_SPRITE_OFFSET);

	m_animations[MustacheGuardStates::Attacking2] = new Animation(L"Resources/animations/enemy/mustache-guard/attack-2.png", 6, 1, 6, true, 80.f, D3DCOLOR_XRGB(120, 193, 152));
	m_animations[MustacheGuardStates::Attacking2]->setPositionX(x);
	m_animations[MustacheGuardStates::Attacking2]->setPositionY(y);

	m_animations[MustacheGuardStates::Moving] = new Animation(L"Resources/animations/enemy/mustache-guard/move.png", 8, 1, 8, true, 100.f, D3DCOLOR_XRGB(120, 193, 152));
	m_animations[MustacheGuardStates::Moving]->setPositionX(x);
	m_animations[MustacheGuardStates::Moving]->setPositionY(y);

	m_animations[MustacheGuardStates::BeingHit] = new Animation(L"Resources/animations/enemy/mustache-guard/being-hit.png", 6, 1, 6, false, 70.f, D3DCOLOR_XRGB(120, 193, 152));
	m_animations[MustacheGuardStates::BeingHit]->setPositionX(x);
	m_animations[MustacheGuardStates::BeingHit]->setPositionY(y - BEING_HIT_SPRITE_OFFSET);

	m_currentState = MustacheGuardStates::Standing;
	m_currentAnimation = m_animations[MustacheGuardStates::Standing];
}


MustacheGuard::~MustacheGuard()
{
	delete m_animations[MustacheGuardStates::Standing];
	delete m_animations[MustacheGuardStates::Attacking1];
	delete m_animations[MustacheGuardStates::Attacking2];
	delete m_animations[MustacheGuardStates::Moving];
}

void MustacheGuard::attachPlayer(Player * player)
{
	m_player = player;
}

void MustacheGuard::checkPositionWithPlayer()
{
	float distance = MathHelper::findDistance(m_player->getPosition(), this->getPosition());
	if (distance <= ATTACK_RANGE)
	{
		m_currentState = MustacheGuardStates::Attacking1;
		m_currentAnimation = m_animations[MustacheGuardStates::Attacking1];
	}
	else
	{
		if (distance <= MOVE_RANGE)
		{
			if (m_player->getPosition().x < (m_initialPosition.x - MOVE_RANGE) ||
				(m_player->getPosition().x > (m_initialPosition.x + MOVE_RANGE)))
			{
				m_currentState = MustacheGuardStates::Standing;
				m_currentAnimation = m_animations[MustacheGuardStates::Standing];
			}
			else
			{
				m_currentState = MustacheGuardStates::Moving;
				m_currentAnimation = m_animations[MustacheGuardStates::Moving];
			}
		}
		else
		{
			m_currentState = MustacheGuardStates::Standing;
			m_currentAnimation = m_animations[MustacheGuardStates::Standing];
		}
	}
}

void MustacheGuard::isHit()
{
	m_isBeingHit = true;
}

Box MustacheGuard::GetBoundingBox()
{
	Box box;

	box.x = x - width / 2 - 20;
	box.y = y - height / 2;
	box.width = width;
	box.height = height;
	box.vx = vx;
	box.vy = vy;

	return box;
}

void MustacheGuard::Update(float deltaTime)
{
	if (m_currentHealth > 0.0f)
	{
		checkPositionWithPlayer();
		if (m_isBeingHit)
		{
			if (m_animations[MustacheGuardStates::BeingHit]->getIsFinished() == false)
			{
				m_currentState = MustacheGuardStates::BeingHit;
				m_currentAnimation = m_animations[MustacheGuardStates::BeingHit];
				checkAndUpdateDirection();
				m_currentAnimation->setPositionX(x);
				m_currentAnimation->setPositionY(y - BEING_HIT_SPRITE_OFFSET);
			}
			else
			{
				m_isBeingHit = false;
				m_animations[MustacheGuardStates::BeingHit]->Reset();
			}
		}
		switch (m_currentState)
		{
		case (MustacheGuardStates::Standing):
		{
			checkAndUpdateDirection();
			m_currentAnimation->setPositionX(x);
			m_currentAnimation->setPositionY(y);
			break;
		}
		case (MustacheGuardStates::Attacking1):
		{
			checkAndUpdateDirection();
			m_currentAnimation->setPositionX(x);
			m_currentAnimation->setPositionY(y - ATTACKING1_SPRITE_OFFSET);
			if (m_currentAnimation->getIsFinished() == true)
			{
				m_isAttackingHit = false;
				m_currentAnimation->Reset();
			}
			break;
		}
		case (MustacheGuardStates::Attacking2):
		{
			checkAndUpdateDirection();
			m_currentAnimation->setPositionX(x);
			m_currentAnimation->setPositionY(y);
			break;
		}
		case (MustacheGuardStates::Moving):
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

void MustacheGuard::checkAndUpdateDirection()
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

bool MustacheGuard::isPlayerOnTheLeft()
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

void MustacheGuard::OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime)
{
}

void MustacheGuard::OnCollision(GameObject * colliableObject, float deltaTime)
{
	if (colliableObject->getTag() == Tag::PlayerTag)
	{
		auto player = dynamic_cast<Player*>(colliableObject);
		if (Collision::getInstance()->isColliding(this->GetBoundingBox(), player->GetBoundingBox()))
		{
			if (m_isAttackingHit == false && player->getCurrentHealth() > 0.0f)
			{
				OutputDebugString(L"[INFO] MustacheGuard attacks Player.\n");
				player->takeDamage(0.5);
				player->isHit();
				m_isAttackingHit = true;
			}
		}
	}
}

void MustacheGuard::Draw()
{
	if (m_currentHealth > 0.0f)
	{
		m_currentAnimation->Draw();
	}
}
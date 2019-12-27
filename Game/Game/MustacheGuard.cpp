#include "stdafx.h"
#include "MustacheGuard.h"

constexpr auto ATTACKING1_SPRITE_OFFSET = 12;
constexpr auto BEING_HIT_SPRITE_OFFSET = 12;

MustacheGuard::MustacheGuard(float x, float y, float width, float height)
	: GameObject(x, y, width, height, Tag::MustaheGuardTag), Health(10)
{
	m_isFacingRight = false;
	m_initialPosition = D3DXVECTOR2(x, y);
	this->setPosition(m_initialPosition);

	m_animations[MustacheGuardStates::Standing] = new Animation(L"Resources/animations/enemy/mustache-guard/Mus-Gaurd-Provocative-59_54_6.png", 6, 1, 6, true, 90.f);
	m_animations[MustacheGuardStates::Standing]->setPositionX(x);
	m_animations[MustacheGuardStates::Standing]->setPositionY(y);

	m_animations[MustacheGuardStates::Attacking1] = new Animation(L"Resources/animations/enemy/mustache-guard/attack-1.png", 5, 1, 5, false, 80.f, D3DCOLOR_XRGB(120, 193, 152));
	m_animations[MustacheGuardStates::Attacking1]->setPositionX(x);
	m_animations[MustacheGuardStates::Attacking1]->setPositionY(y - ATTACKING1_SPRITE_OFFSET);

	m_animations[MustacheGuardStates::Attacking2] = new Animation(L"Resources/animations/enemy/mustache-guard/Mus-Gaurd-Attack1-95_52_6.png", 6, 1, 6, true, 80.f);
	m_animations[MustacheGuardStates::Attacking2]->setPositionX(x);
	m_animations[MustacheGuardStates::Attacking2]->setPositionY(y);

	m_animations[MustacheGuardStates::Moving] = new Animation(L"Resources/animations/enemy/mustache-guard/Mus-Gaurd-Moving-57-56-8.png", 8, 1, 8, true, 100.f);
	m_animations[MustacheGuardStates::Moving]->setPositionX(x);
	m_animations[MustacheGuardStates::Moving]->setPositionY(y);

	m_animations[MustacheGuardStates::BeingHit] = new Animation(L"Resources/animations/enemy/mustache-guard/Mus-Gaurd-BeHit-74_71_6.png", 6, 1, 6, false, 70.f);
	m_animations[MustacheGuardStates::BeingHit]->setPositionX(x);
	m_animations[MustacheGuardStates::BeingHit]->setPositionY(y - BEING_HIT_SPRITE_OFFSET);

	isDead = false;
	m_animations[MustacheGuardStates::Burst] = new Animation(L"Resources/Enmity/PNG/burst-bat_88_56_8.png", 8, 1, 8, false, 60.f);
	m_animations[MustacheGuardStates::Burst]->setPositionX(x);
	m_animations[MustacheGuardStates::Burst]->setPositionY(y);

	m_currentState = MustacheGuardStates::Standing;
	m_currentAnimation = m_animations[MustacheGuardStates::Standing];
}

MustacheGuard::~MustacheGuard()
{
	delete m_animations[MustacheGuardStates::Standing];
	delete m_animations[MustacheGuardStates::Attacking1];
	delete m_animations[MustacheGuardStates::Attacking2];
	delete m_animations[MustacheGuardStates::Moving];
	delete m_animations[MustacheGuardStates::Burst];
}

void MustacheGuard::attachPlayer(Player * player)
{
	m_player = player;
}

void MustacheGuard::checkPositionWithPlayer()
{
	float distance = MathHelper::findDistance(m_player->getPosition(), this->getPosition());
	if (distance <= m_attackRange)
	{
		m_currentState = MustacheGuardStates::Attacking1;
		m_currentAnimation = m_animations[MustacheGuardStates::Attacking1];
	}
	else
	{
		if (distance <= m_moveRange)
		{
			if (m_player->getPosition().x < (m_initialPosition.x - m_moveRange) ||
				(m_player->getPosition().x > (m_initialPosition.x + m_moveRange)))
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
	Sound::getInstance()->play(SoundNames::GUARD_HIT_1_SOUND, false);
}

Box MustacheGuard::GetBoundingBox()
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

Box MustacheGuard::GetBoundingBoxForApple()
{
	Box box;

	switch (m_currentState)
	{
	case MustacheGuardStates::Standing: case MustacheGuardStates::Moving: case MustacheGuardStates::MovingOnLava: case MustacheGuardStates::BeingHit:
		box.x = x;
		box.y = y;
		box.width = 40;
		box.height = 65;
		box.vx = vx;
		box.vy = vy;
		break;
	case MustacheGuardStates::Attacking1:
		if (m_isFacingRight)
			box.x = x - 30;
		else
			box.x = x + 30;
		box.y = y + 10;
		box.width = 60;
		box.height = 60;
		box.vx = vx;
		box.vy = vy;
		break;
	case MustacheGuardStates::Attacking2:
		if (m_isFacingRight)
			box.x = x - 20;
		else
			box.x = x + 20;
		box.y = y;
		box.width = 40;
		box.height = 60;
		box.vx = vx;
		box.vy = vy;
		break;
	case MustacheGuardStates::Burst:
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
	else {
		if (!isDead) {
			m_currentState = MustacheGuardStates::Burst;
			m_currentAnimation = m_animations[MustacheGuardStates::Burst];
			m_currentAnimation->setPositionX(x);
			m_currentAnimation->setPositionY(y);
			if (m_currentAnimation->getIsFinished())
				isDead = true;
			m_currentAnimation->Update(deltaTime);
		}

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
		m_isFacingRight = false;
		return true;
	}
	else
	{
		m_isFacingRight = true;
		return false;
	}
}

void MustacheGuard::OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime)
{
}

void MustacheGuard::OnCollision(GameObject * colliableObject, float deltaTime)
{
	if (m_currentHealth > 0 && !isDead)
	{
		if (colliableObject->getTag() == PlayerTag) {
			auto player = dynamic_cast<Player*>(colliableObject);
			if (Collision::getInstance()->isColliding(this->GetBoundingBox(), player->GetBoundingBox()))
			{
				if (m_isAttackingHit == false && player->getCurrentHealth() > 0.0f)
				{
					OutputDebugString(L"[INFO] MustacheGuard attacks Player.\n");
					player->takeDamage(1);
					player->isHit();
					m_isAttackingHit = true;
				}
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
	else
	{
		if (!isDead)
		{
			m_currentAnimation->Draw();
		}
	}
}

void MustacheGuard::setAttackRange(int value)
{
	m_attackRange = value;
}

void MustacheGuard::setMoveRange(int value)
{
	m_moveRange = value;
}

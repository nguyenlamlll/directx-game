#include "stdafx.h"
#include "Ball.h"

Ball::Ball(float x, float y, float width, float height, LPCWSTR spritePath)
	: GameObject(x, y, width, height, Tag::UnclassifiedTag)
{
	m_ballSprite = new Sprite(spritePath);
	m_ballSprite->setPositionX(x);
	m_ballSprite->setPositionY(y);
	isFirstStarted = true;

	ballSpeed = 0.6;
	ballVerticalSpeed = 0.0;
}

Ball::~Ball()
{
}

void Ball::setRandomInitialSpeed(float deltaTime)
{
	vx = ballSpeed * deltaTime;
	vy = ballVerticalSpeed * deltaTime;
}

void Ball::assignPadsCanCollideBall(Pad* leftPad, Pad* rightPad)
{
	m_leftPad = leftPad;
	m_rightPad = rightPad;
}

Box Ball::GetBoundingBox()
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

void Ball::Update(float deltaTime)
{
#ifdef _DEBUG
	//std::wstring raw = L"[INFO] Ball position: (" + std::to_wstring(x) + L", " + std::to_wstring(y) + L")";
	//OutputDebugString(raw.c_str());
	//OutputDebugString(L"\n");
#endif
	if (isFirstStarted)
	{
		isFirstStarted = false;
		setRandomInitialSpeed(deltaTime);
	}

	float normalX, normalY;
	auto collisionResult = Collision::getInstance()->SweptAABB(this->GetBoundingBox(), m_rightPad->GetBoundingBox(), normalX, normalY, deltaTime);
	if (collisionResult.isCollide)
	{
		vx = - ballSpeed * deltaTime;
		if (abs(normalY) > 0.0001f)
			vy = -vy;

		vy = m_rightPad->getVelocity().y;
	}

	auto leftPadCollisionResult = Collision::getInstance()->SweptAABB(this->GetBoundingBox(), m_leftPad->GetBoundingBox(), normalX, normalY, deltaTime);
	if (leftPadCollisionResult.isCollide)
	{
		vx = ballSpeed * deltaTime;
		if (abs(normalY) > 0.0001f)
			vy = -vy;

		vy = m_leftPad->getVelocity().y;
	}

	// If ball hits upper border
	if (m_ballSprite->getPositionY() <= 0) {
		vy = -vy;
	}
	// If ball hits lower border
	if (m_ballSprite->getPositionY() >= Global::GetInstance()->g_ScreenHeight - 20) {
		vy = -vy;
	}


	m_ballSprite->setPositionX(m_ballSprite->getPositionX() + vx);
	m_ballSprite->setPositionY(m_ballSprite->getPositionY() + vy);
	x = m_ballSprite->getPositionX();
	y = m_ballSprite->getPositionY();

#ifdef _DEBUG
	//std::wstring info = L"[INFO] Ball vx, vy: " + std::to_wstring(vx) + L", " + std::to_wstring(vy) + L")";
	//OutputDebugString(info.c_str());
	//OutputDebugString(L"\n");
#endif
}

void Ball::Draw()
{
	m_ballSprite->Draw();
}

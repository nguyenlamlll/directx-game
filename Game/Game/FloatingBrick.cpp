#include "stdafx.h"
#include "FloatingBrick.h"

FloatingBrick::FloatingBrick(float x, float y, float width, float height, int type) : GameObject(x, y, width, height, Tag::BrickTag) {
	this->setPosition(D3DXVECTOR2(x, y));
	// start marking time
	start_wait = GetTickCount();
	/*
	0: get out
	1 : get in
	*/

	m_brickInside = new Animation(L"Resources/Enmity/PNG/brick-go-inside_40_24_5.png", 5, 1, 5, false, 400.f);
	m_brickOutside = new Animation(L"Resources/Enmity/PNG/brick-go-outside_40_24_5.png", 5, 1, 5, false, 400.f);

	switch (type)
	{
	case 1:
	{
		image = m_brickInside;
		state = GoInside;
		break;
	}
	case 0:
	{
		image = m_brickOutside;
		state = GoOutside;
		break;
	}
	default:
		break;
	}
	image->setPositionX(x);
	image->setPositionY(y);
	vx = 0;
	vy = 0;
}

FloatingBrick::~FloatingBrick() {
	if (m_brickInside != NULL)
	{
		delete m_brickInside;
		m_brickInside = nullptr;
	}
	if (m_brickOutside != NULL)
	{
		delete m_brickOutside;
		m_brickOutside = nullptr;
	}
}

Box FloatingBrick::GetBoundingBox() {
	Box box;

	box.x = x - width/2;
	box.y = y - height/2;
	box.width = width;
	box.height = height;
	box.vx = vx;
	box.vy = vy;

	return box;
}

D3DXVECTOR2 FloatingBrick::getVelocity() {
	D3DXVECTOR2 result(vx, vy);
	return result;
}

void FloatingBrick::Update(float deltaTime) {

	ChangeDirection();
	image->Update(deltaTime);
}

void FloatingBrick::ChangeDirection() {
	switch (state)
	{
	case GoInside: {
		// set value check collision
		switch (image->getIndexFrame())
		{
		case 0: case 1: case 2:
			status = Allow;
			break;
		case 3: case 4:
			status = NotAllow;
		default:
			break;
		}
		// check time wait and change state
		if (image->getIsFinished()) {
			// get current time
			DWORD now = GetTickCount();
			if (now - start_wait > 3500)
			{
				// change animation
				//ChangeState(GoOutside);
				image = m_brickOutside;
				image->Reset();
				image->setPositionX(x);
				image->setPositionY(y);
				vx = 0;
				vy = 0;
				state = GoOutside;
				// reset start marking time
				start_wait = GetTickCount();
			}
		}
		break;
	}
	case GoOutside: {
		// set value check collision
		switch (image->getIndexFrame())
		{
		case 0: case 1:
			status = NotAllow;
			break;
		case 2: case 3: case 4:
			status = Allow;
			break;
		default:
			break;
		}
		// check time wait and change state
		if (image->getIsFinished()) {
			// get current time
			DWORD now = GetTickCount();
			if (now - start_wait > 3500)
			{
				// change animation
				//ChangeState(GoInside);
				image = m_brickInside;
				image->Reset();
				image->setPositionX(x);
				image->setPositionY(y);
				vx = 0;
				vy = 0;
				state = GoInside;
				// reset start marking time
				start_wait = GetTickCount();
			}
		}
		break;
	}
	default:
		break;
	}
}

void FloatingBrick::OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime) {
	// get status to do allow player standing above brick
}

void FloatingBrick::Draw() {
	image->Draw();
}

Status FloatingBrick::getStatus() {
	return status;
}

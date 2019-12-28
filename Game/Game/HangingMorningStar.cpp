#include "stdafx.h"
#include "HangingMorningStar.h"

HangingMorningStar::HangingMorningStar(float x, float y, float width, float height, int indexFrame) : GameObject(x, y, width, height, Tag::HangingMorningStarTag) {
	this->setPosition(D3DXVECTOR2(x, y));
	// start marking time
	start_wait = GetTickCount();
	/*
	0: get out
	1 : get in
	*/

	m_morningStarInside = new Animation(L"Resources/Enmity/PNG/HangingMorningStar-go-inside_34_67_15.png", 15, 1, 15, indexFrame, false, 90.f);
	m_morningStarOutside = new Animation(L"Resources/Enmity/PNG/HangingMorningStar-go-outside_34_67_15.png", 15, 1, 15, false, 90.f);

	image = m_morningStarInside;
	state = GoInside;
	image->setPositionX(x);
	image->setPositionY(y);
	vx = 0;
	vy = 0;
}

HangingMorningStar::~HangingMorningStar() {
	if (m_morningStarInside != NULL)
	{
		delete m_morningStarInside;
		m_morningStarInside = nullptr;
	}
	if (m_morningStarOutside != NULL)
	{
		delete m_morningStarOutside;
		m_morningStarOutside = nullptr;
	}
}

Box HangingMorningStar::GetBoundingBox() {
	Box box;

	box.x = x - width / 2;
	box.y = y - height / 2;
	box.width = width - 10;
	box.height = height + 30;
	box.vx = vx;
	box.vy = vy;

	return box;
}

D3DXVECTOR2 HangingMorningStar::getVelocity() {
	D3DXVECTOR2 result(vx, vy);
	return result;
}

void HangingMorningStar::Update(float deltaTime) {
	ChangeDirection();
	image->Update(deltaTime);
}

void HangingMorningStar::OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime) {

}

void HangingMorningStar::Draw() {
	image->Draw();
}

void HangingMorningStar::ChangeDirection() {
	switch (state)
	{
	case GoInside: {
		// set value check collision
		switch (image->getIndexFrame())
		{
		case 0: case 1: case 2: case 3: case 4: case 5:
			status = Damage;
			break;
		case 6: case 7: case 8: case 9: case 10: case 11: case 12: case 13: case 14:
			status = NotDamage;
		default:
			break;
		}
		// check time wait and change state
		if (image->getIsFinished()) {
			// get current time
			DWORD now = GetTickCount();
			if (now - start_wait > 100)
			{
				// change animation
				//ChangeState(GoOutside);
				image = m_morningStarOutside;
				image->Reset();
				image->setPositionX(x);
				image->setPositionY(y);
				vx = 0;
				vy = 0;
				//m_isAttackingHit = false;
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
		case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
			status = NotDamage;
			break;
		case 10: case 11: case 12: case 13: case 14: case 15:
			status = Damage;
			break;
		default:
			break;
		}
		// check time wait and change state
		if (image->getIsFinished()) {
			// get current time
			DWORD now = GetTickCount();
			if (now - start_wait > 100)
			{
				// change animation
				//ChangeState(GoInside);
				image = m_morningStarInside;
				image->Reset();
				image->setPositionX(x);
				image->setPositionY(y);
				vx = 0;
				vy = 0;
				m_isAttackingHit = false;
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

StatusDamage HangingMorningStar::getStatus() {
	return status;
}

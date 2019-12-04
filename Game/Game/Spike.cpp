#include "stdafx.h"
#include "Spike.h"

Spike::Spike(float x, float y, float width, float height, int type) : GameObject(x, y, width, height, Tag::SpikeTag) {
	//this->setPosition(D3DXVECTOR2(x, y));
	// start marking time
	start_wait = GetTickCount();

	/*
	0: get out
	1 : get in
	*/

	m_spikeInside = new Animation(L"Resources/Enmity/PNG/spike-go-inside_49_35_6.png", 6, 1, 6, false, 200.f);
	m_spikeOutside = new Animation(L"Resources/Enmity/PNG/spike-go-outside_49_35_6.png", 6, 1, 6, false, 200.f);

	switch (type)
	{
	case 1:
	{
		image = m_spikeInside;
		state = GoInside;
		break;
	}
	case 0:
	{
		image = m_spikeOutside;
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

Spike::~Spike() {
	if (m_spikeInside != NULL)
	{
		delete m_spikeInside;
		m_spikeInside = nullptr;
	}
	if (m_spikeOutside != NULL)
	{
		delete m_spikeOutside;
		m_spikeOutside = nullptr;
	}
}

Box Spike::GetBoundingBox() {
	Box box;

	box.x = x;
	box.y = y;
	box.width = width;
	box.height = height;
	box.vx = vx;
	box.vy = vy;

	return box;
}

D3DXVECTOR2 Spike::getVelocity() {
	D3DXVECTOR2 result(vx, vy);
	return result;
}

void Spike::Update(float deltaTime) {
	ChangeDirection();
	image->Update(deltaTime);
}

void Spike::OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime) {

}

void Spike::Draw() {
	image->Draw();
}

void Spike::ChangeDirection() {
	switch (state)
	{
	case GoInside: {
		// set value check collision
		switch (image->getIndexFrame())
		{
		case 0: case 1: case 2: case 3:
			status = Damage;
			break;
		case 4: case 5:
			status = NotDamage;
		default:
			break;
		}
		// check time wait and change state
		if (image->getIsFinished()) {
			// get current time
			DWORD now = GetTickCount();
			if (now - start_wait > 4000)
			{
				// change animation
				image = m_spikeOutside;
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
			status = NotDamage;
			break;
		case 2: case 3: case 4: case 5:
			status = Damage;
			break;
		default:
			break;
		}
		// check time wait and change state
		if (image->getIsFinished()) {
			// get current time
			DWORD now = GetTickCount();
			if (now - start_wait > 1500)
			{
				// change animation
				image = m_spikeInside;
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

StatusDamage Spike::getStatus() {
	return status;
}

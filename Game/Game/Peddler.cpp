#include "stdafx.h"
#include "Peddler.h"

Peddler::Peddler(float x, float y, float width, float height) : GameObject(x, y, width, height, Tag::PeddlerTag) {
	status = PeddlerStatus::NonActive;
	this->setPosition(D3DXVECTOR2(x, y));

	isUsed = false;
	isDead = false;
	isDied = false;
	isTransform = false;

	// start marking time
	start_wait = GetTickCount();
	m_state = PeddlerTransform_1;
	// peddler start

	m_imageTrf1 = new Animation(L"Resources/Items/PNG/peddlerTransform1_125_88_10.png", 10, 1, 10, false, 70.f);
	m_imageTrf2 = new Animation(L"Resources/Items/PNG/peddlerTransform2_136_89_7.png", 7, 1, 7, false, 70.f);
	m_imageTrf3 = new Animation(L"Resources/Items/PNG/peddlerTransform3_150_67_6.png", 6, 1, 6, false, 70.f);
	m_imageTrf4 = new Animation(L"Resources/Items/PNG/peddlerTransform4_138_83_7.png", 7, 1, 7, false, 70.f);

	m_imageStanding1 = new Animation(L"Resources/Items/PNG/peddler-stand_30_56_7.png", 7, 1, 7, false, 100.f);
	m_imageStanding2 = new Animation(L"Resources/Items/PNG/peddler-stand-long_74_57_14.png", 14, 1, 14, false, 100.f);

	m_image = m_imageStanding1;
	vy = 0;
	vx = 0;
	m_image->setPositionX(x);
	m_image->setPositionY(y);
}

Peddler::~Peddler() {
	if (m_imageTrf1 != NULL) { delete m_imageTrf1; m_imageTrf1 = nullptr;}
	if (m_imageTrf2 != NULL) { delete m_imageTrf2; m_imageTrf2 = nullptr;}
	if (m_imageTrf3 != NULL) { delete m_imageTrf3; m_imageTrf3 = nullptr;}
	if (m_imageTrf4 != NULL) { delete m_imageTrf4; m_imageTrf4 = nullptr;}
	if (m_imageStanding1 != NULL) { delete m_imageStanding1; m_imageStanding1 = nullptr;}
	if (m_imageStanding2 != NULL) { delete m_imageStanding2; m_imageStanding2 = nullptr;}
}

Box Peddler::GetBoundingBox() {
	Box box;

	box.x = x;
	box.y = y;
	box.width = width;
	box.height = height;
	box.vx = vx;
	box.vy = vy;

	return box;
}

D3DXVECTOR2 Peddler::getVelocity() {
	D3DXVECTOR2 result(vx, vy);
	return result;
}

void Peddler::Update(float deltaTime) {
	OnInterSerct();
	if (!isUsed)
		NonActiveAction();
	else
		ActiveAction();
	m_image->Update(deltaTime);
	if (isTransform) {
		m_imageStanding2->Update(deltaTime);
		if (m_imageStanding2->getIsFinished()) {
			DWORD now = GetTickCount();
			if (now - start_waitStanding2 > 2500)
			{
				// reset animation
				m_imageStanding2->Reset();
				// reset start marking time
				start_waitStanding2 = GetTickCount();
			}
		}
	}
	
}

void Peddler::Draw() {
	if (!isDead) {
		m_image->Draw();
		if (isTransform)
			m_imageStanding2->Draw();

	}
}

void Peddler::OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime) {
	// to do change status type when happen collision

	// when peddler leave camera todo call resetPeddler();
}

void Peddler::changeState(PeddlerStates state) {
	switch (state)
	{
	case PeddlerTransform_1:
		this->m_state = state;
		m_imageTrf1->Reset();
		m_image = m_imageTrf1;
		m_image->setPositionX(this->x);
		m_image->setPositionY(this->y-15);
		break;
	case PeddlerTransform_2:
		this->m_state = state;
		m_imageTrf2->Reset();
		m_image = m_imageTrf2;
		m_image->setPositionX(this->x+2);
		m_image->setPositionY(this->y-8);
		break;
	case PeddlerTransform_3:
		this->m_state = state;
		m_imageTrf3->Reset();
		m_image = m_imageTrf3;
		m_image->setPositionX(this->x);
		m_image->setPositionY(this->y+3);
		break;
	case PeddlerTransform_4:
		this->m_state = state;
		m_imageTrf4->Reset();
		m_image = m_imageTrf4;
		m_image->setPositionX(this->x);
		m_image->setPositionY(this->y-12);
		break;
	default:
		break;
	}
}

void Peddler::ActiveAction() {
	// when happen collision, change animation, then delete this
	switch (status)
	{
	case PeddlerStatus::Active:
	{
		switch (m_state)
		{
		case PeddlerTransform_1:
			if (m_image->getIsFinished()) {
				changeState(PeddlerTransform_2);
			}
			break;
		case PeddlerTransform_2:
			if (m_image->getIsFinished()) {
				changeState(PeddlerTransform_3);
			}
			break;
		case PeddlerTransform_3:
			if (m_image->getIsFinished()) {
				changeState(PeddlerTransform_4);
			}
			break;
		case PeddlerTransform_4:
			if (m_image->getIndexFrame()==2) {
				isTransform = true;
				m_imageStanding2->setPositionX(this->x + 60);
				m_imageStanding2->setPositionY(this->y);
				start_waitStanding2 = GetTickCount();
			}
			break;
		default:
			break;
		}
		
		break;
	}
	default:
	{
		changeState(PeddlerTransform_1);
		isDied = true;
		isUsed = true;
		status = PeddlerStatus::Active;
		break;
	}
	}
}

void Peddler::NonActiveAction() {
	if (m_image->getIsFinished())
	{
		// get current time
		DWORD now = GetTickCount();
		if (now - start_wait > 1500)
		{
			// reset animation
			m_image->Reset();
			// reset start marking time
			start_wait = GetTickCount();
		}
	}
}


void Peddler::resetPeddler() {
	status = PeddlerStatus::NonActive;

	isUsed = false;
	isDead = false;
	isDied = false;

	// start marking time
	start_wait = GetTickCount();

	// peddler start
	m_image = m_imageStanding1;
	m_image->setPositionX(this->x);
	m_image->setPositionY(this->y);
	isTransform = false;
}

void Peddler::attachPlayer(Player* player)
{
	m_player = player;
}

void Peddler::OnInterSerct() {
	float rangeX, rangeY;
	rangeX = abs(m_player->getPosition().x - this->x);
	rangeY = abs(m_player->getPosition().y - this->y);

	if (rangeX <= 60 && rangeY <= 40)
	{
		ActiveAction();
	}

	if (rangeX > 200 || rangeY > 150)
		resetPeddler();
}
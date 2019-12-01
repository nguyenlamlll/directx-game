#include "stdafx.h"
#include "Peddler.h"

Peddler::Peddler(float x, float y, float width, float height) : GameObject(x, y, width, height, Tag::PeddlerTag) {
	status = NonActive;
	this->setPosition(D3DXVECTOR2(x, y));

	isUsed = false;
	isDead = false;
	isDied = false;

	// start marking time
	start_wait = GetTickCount();

	// peddler start
	image1 = new Animation(L"Resources/Items/PNG/peddler-stand_30_56_7.png", 7, 1, 7, true, 40.f);
	image1->setPositionX(x);
	image1->setPositionY(y);
}

Peddler::~Peddler() {
	if (image1 != NULL)
	{
		delete image1;
		image1 = nullptr;
	}
	if (image2 != NULL)
	{
		delete image2;
		image2 = nullptr;
	}
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
	switch (status)
	{
	case NonActive:
		NonActiveAction();
		image1->Update(deltaTime);
		break;
	case Active:
		ActiveAction();
		if (!isDead) {
			image1->Update(deltaTime);

			if(state==PeddlerTransform_4){ 
				image2->Update(deltaTime);
			}
		}
		break;
	default:
		break;
	}
}

void Peddler::Draw() {
	if (!isDead) {
		image1->Draw();
		image2->Draw();
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
		this->state = state;
		image1 = new Animation(L"Resources/Items/PNG/peddlerTransform1_125_88_10.png", 10, 1, 10, false, 80.f);
		image1->setPositionX(this->x);
		image1->setPositionY(this->y);
		vy = 0;
		vx = 0;
		break;
	case PeddlerTransform_2:
		this->state = state;
		image1 = new Animation(L"Resources/Items/PNG/peddlerTransform2_136_89_7.png", 7, 1, 7, false, 80.f);
		image1->setPositionX(this->x);
		image1->setPositionY(this->y);
		vy = 0;
		vx = 0;
		break;
	case PeddlerTransform_3:
		this->state = state;
		image1 = new Animation(L"Resources/Items/PNG/peddlerTransform3_150_67_6.png", 6, 1, 6, false, 80.f);
		image1->setPositionX(this->x);
		image1->setPositionY(this->y);
		vy = 0;
		vx = 0;
		break;
	case PeddlerTransform_4:
		this->state = state;
		image1 = new Animation(L"Resources/Items/PNG/peddlerTransform4_138_83_7.png", 7, 1, 7, false, 80.f);
		image1->setPositionX(this->x);
		image1->setPositionY(this->y);
		vy = 0;
		vx = 0;
		break;
	default:
		break;
	}
}

void Peddler::ActiveAction() {
	// when happen collision, change animation, then delete this
	switch (status)
	{
	case Active:
	{
		switch (state)
		{
		case PeddlerTransform_1:
			if (image1->getIsFinished()) {
				changeState(PeddlerTransform_2);
			}
			break;
		case PeddlerTransform_2:
			if (image1->getIsFinished()) {
				changeState(PeddlerTransform_3);
			}
			break;
		case PeddlerTransform_3:
			if (image1->getIsFinished()) {
				changeState(PeddlerTransform_4);
			}
			break;
		case PeddlerTransform_4:
			if (image1->getIsFinished()) {
				image2 = new Animation(L"Resources/Items/PNG/peddlerTransform4_138_83_7.png", 7, 1, 7, true, 80.f);
				image2->setPositionX(this->x + 50);
				image2->setPositionY(this->y);
				vy = 0;
				vx = 0;
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
		status = Active;
		break;
	}
	}
}

void Peddler::NonActiveAction() {
	if (image1->getIsFinished())
	{
		// get current time
		DWORD now = GetTickCount();
		if (now - start_wait > 3500)
		{
			// reset animation
			image1->Reset();
			// reset start marking time
			start_wait = GetTickCount();
		}
	}
}


void Peddler::resetPeddler() {
	status = NonActive;

	isUsed = false;
	isDead = false;
	isDied = false;

	// start marking time
	start_wait = GetTickCount();

	// peddler start
	image1 = new Animation(L"Resources/Items/PNG/peddler-stand_30_56_7.png", 7, 1, 7, true, 40.f);
	image1->setPositionX(this->x);
	image1->setPositionY(this->y);
}
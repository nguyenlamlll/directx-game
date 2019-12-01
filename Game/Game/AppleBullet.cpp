#include "stdafx.h"
#include "AppleBullet.h"



AppleBullet::AppleBullet(float x, float y, float width, float height, Player* player)
	: GameObject(x, y, width, height, Tag::BulletAppleTag){

	this->setPosition(D3DXVECTOR2(x, y));
	
	isUsed= false;
	isDead = false;
	isDied = false;
	
	// Fling
	image = new Animation(L"Resources/Items/PNG/apple-fling_12_12_4.png", 4, 1, 4, true, 50.f);
	switch (player->getCurrentState()->GetState())
	{
	case StandingThrow: {
		image->setPositionY((player->top() + player->bottom()) / 2);
		this->vy = -0.45f;
		if (!player->getIsFacingRight()) {
			this->vx = 2.0f;
			// Bullet's postionX = player's positionX + player's width
			image->setPositionX(player->right());
		}
		else {
			this->vx = -2.0f;
			// Bullet's postionX = player's positionX 
			image->setPositionX(player->left());
		}
		break;
	}
	case StandAttackThrow: {
		image->setPositionY((player->top() + player->bottom()) / 2);
		this->vy = -0.45f;
		if (!player->getIsFacingRight()) {
			this->vx = 2.0f;
			// Bullet's postionX = player's positionX + player's width
			image->setPositionX(player->right());
		}
		else {
			this->vx = -2.0f;
			// Bullet's postionX = player's positionX 
			image->setPositionX(player->left());
		}
		break;
	}
	case JumpAttackThrow: {
		image->setPositionY((player->top() + player->bottom()) / 2);
		this->vy = -0.45f;
		if (!player->getIsFacingRight()) {
			this->vx = 2.0f;
			// Bullet's postionX = player's positionX + player's width
			image->setPositionX(player->right());
		}
		else {
			this->vx = -2.0f;
			// Bullet's postionX = player's positionX 
			image->setPositionX(player->left());
		}
		break;
	}
	case SwingAttackThrow: {
		image->setPositionY((player->top() + player->bottom()) / 2);
		this->vy = -0.45f;
		if (!player->getIsFacingRight()) {
			this->vx = 2.0f;
			// Bullet's postionX = player's positionX + player's width
			image->setPositionX(player->right());
		}
		else {
			this->vx = -2.0f;
			// Bullet's postionX = player's positionX 
			image->setPositionX(player->left());
		}
		break;
	}
	default:
		break;
	}
	this->m_isFacingRight = player->getIsFacingRight();
}

AppleBullet::~AppleBullet() {
	
}


Box AppleBullet::GetBoundingBox() {
	Box box;

	box.x = x;
	box.y = y;
	box.width = width;
	box.height = height;
	box.vx = vx;
	box.vy = vy;

	return box;
}

D3DXVECTOR2 AppleBullet::getVelocity() {
	D3DXVECTOR2 result(vx, vy);
	return result;
}

void AppleBullet::Update(float deltaTime) {
	switch (status)
	{
	case Burst: {
		BurstAction();
		if (!isDead) {
			image->Update(deltaTime);
		}
		break;
	}
	case Fling: {
		x += vx;
		y += vy;
		image->Update(deltaTime);
		break;
	}
	default:
		break;
	}
}

void AppleBullet::BurstAction() {
	switch (status)
	{
	case Burst:
	{
		if (image->getIsFinished())
		{
			isDead = true;
			// to do delete apple in list object
		}
		break;
	}
	default:
	{
		vx = 0;
		vy = 0;
		image = new Animation(L"Resources/Items/PNG/genie-jar_34_38_10.png", 10, 1, 10, false, 70.f);
		image->setPositionX(this->x);
		image->setPositionY(this->y);
		isDied = true;
		status = Burst;
		break;
	}
	}
}


void AppleBullet::Draw() {
	//m_playerSprite->Draw();
	if(status == Burst && image->getIsFinished() == true){ }
	else {
		image->Draw();
	}
	//m_currentAnimation->Draw();
}


void AppleBullet::OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime) {
	// to do change status type when happen collision
}





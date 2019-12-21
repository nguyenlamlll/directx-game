#include "stdafx.h"
#include "Skeleton.h"

#define ATTACK_RANGE 120


Skeleton::Skeleton(float x, float y, float width, float height, bool isFacingRight) : 
	GameObject(x, y, width, height, Tag::SkeletonTag), Health(1)
{
	this->setPosition(D3DXVECTOR2(x, y));
	isDead = false;
	isDied = false;
	isUsed = false;

	m_startWait = GetTickCount();
	// 1 == true || 0 == false
	m_isFacingRight = isFacingRight;

	//image = new Animation;
	m_imageCrawl = new Animation(L"Resources/Enmity/PNG/skeleton_108_111_1.png", 1, 1, 1, false, 10.f);
	m_imageBurst = new Animation(L"Resources/Enmity/PNG/burst-skeleton_88_56_8.png", 8, 1, 8, false, 50.f);
	m_imageTransform = new Animation(L"Resources/Enmity/PNG/skeleton-star_108_111_20.png", 20, 1, 20, false, 220.f);

	m_image = m_imageCrawl;
	m_image->setFlipHorizontal(m_isFacingRight);
	m_image->setPositionX(x);
	m_image->setPositionY(y);
	vx = 0;
	vy = 0;
	m_state = SkeletonCrawl;
}

Skeleton::~Skeleton() {
	if (m_imageCrawl != NULL){ delete m_imageCrawl; m_imageCrawl = nullptr; }
	if (m_imageBurst != NULL){ delete m_imageBurst; m_imageBurst = nullptr; }
	if (m_imageTransform != NULL){ delete m_imageTransform; m_imageTransform = nullptr; }
}

void Skeleton::deinitialize()
{
	if (m_isDeinitialized == false)
	{
		delete m_imageCrawl;
		delete m_imageBurst;
		delete m_imageTransform;
		m_isDeinitialized = true;
	}
}

Box Skeleton::GetBoundingBox() {
	Box box;

	box.x = x;
	box.y = y;
	box.width = width;
	box.height = height;
	box.vx = vx;
	box.vy = vy;

	return box;
}

D3DXVECTOR2 Skeleton::getVelocity() {
	D3DXVECTOR2 result(vx, vy);
	return result;
}

void Skeleton::Update(float deltaTime) {
	if (!isDead && this->m_currentHealth > 0.0f) {
		checkPositionWithPlayer();
		switch (m_state)
		{
		case SkeletonCrawl:
			break;
		case SkeletonTransform:
			TransformAction();
			break;
		case SkeletonBurst:
			BurstAction();
			break;
		case SkeletonAttact:
			AttactAction();
			break;
		default:
			break;
		}
		m_image->Update(deltaTime);
	}

	if (!isDead && m_currentHealth <= 0.0f)
	{
		BurstAction();
		m_image->Update(deltaTime);
	}
}

void Skeleton::Draw() {
	if (!isDead) {
		m_image->Draw();
	}
}

void Skeleton::OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime) {

}

void Skeleton::attachPlayer(Player* player) {
	m_player = player;
}

void Skeleton::checkPositionWithPlayer() {
	float distanceX, distanceY;
	distanceX = abs(m_player->left() - this->x);

	distanceY = m_player->top() - this->y;
	if (distanceX <= ATTACK_RANGE && !isUsed)
	{
		if (distanceY > 0 && distanceY <= ATTACK_RANGE) {
			TransformAction();
		}

	}
	if (distanceX >= ATTACK_RANGE && isUsed == true && isDead==false)
	{
		ResetAction();
		if (abs(distanceY) >= ATTACK_RANGE) {
			//ResetAction();
		}

	}
}

void Skeleton::ResetAction() {
	
	m_state = SkeletonCrawl;

	m_startWait = GetTickCount();
	isUsed = false;
	//image = new Animation;
	m_imageCrawl->Reset();
	m_image = m_imageCrawl;
	m_image->setFlipHorizontal(m_isFacingRight);
	m_image->setPositionX(x);
	m_image->setPositionY(y);
	vx = 0;
	vy = 0;
	m_state = SkeletonCrawl;
}

void Skeleton::TransformAction() {
	switch (m_state)
	{
	case SkeletonTransform: {
		if (m_image->getIsFinished()) {
			m_state = SkeletonAttact;
			isDied = true;
			isDead = true;
		}
		break;
	}
	default:
		m_state = SkeletonTransform;
		m_imageTransform->Reset();
		m_image = m_imageTransform;
		m_image->setFlipHorizontal(m_isFacingRight);
		m_image->setPositionX(this->x);
		m_image->setPositionY(this->y);
		isUsed = true;
		break;
	}
}

void Skeleton::BurstAction() {
	switch (m_state)
	{
	case SkeletonBurst: {
		if (m_image->getIsFinished()) {
			isDied = true;
			isDead = true;
		}
		break;
	}
	default:
		m_state = SkeletonBurst;
		m_imageBurst->Reset();
		m_image = m_imageBurst;
		m_image->setFlipHorizontal(m_isFacingRight);
		m_image->setPositionX(this->x);
		m_image->setPositionY(this->y);
		isUsed = true;
		break;
	}

	if (isDead == true)
	{
		deinitialize();
	}
}

void Skeleton::AttactAction() {
	// to do create bom bone
			//{


			//     }
}

//get state
SkeletonState Skeleton::getState() {
	return m_state;
}

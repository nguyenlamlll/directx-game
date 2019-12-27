#include "stdafx.h"
#include "Skeleton.h"

#define ATTACK_RANGE 180


Skeleton::Skeleton(float x, float y, float width, float height, bool isFacingRight) : 
	GameObject(x, y, width, height, Tag::SkeletonTag), Health(10)
{
	this->setPosition(D3DXVECTOR2(x, y));
	isDead = false;
	isUsed = false;
	m_startWait = GetTickCount();
	// 1 == true || 0 == false
	m_isFacingRight = isFacingRight;

	//image = new Animation;
	m_imageCrawl = new Animation(L"Resources/Enmity/PNG/skeleton_108_111_1.png", 1, 1, 1, false, 10.f);
	m_imageBurst = new Animation(L"Resources/Enmity/PNG/burst-bat_88_56_8.png", 8, 1, 8, false, 60.f);
	m_imageTransform = new Animation(L"Resources/Enmity/PNG/skeleton-star_108_111_20.png", 20, 1, 20, false, 100.f);

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

	for (auto p : list)
	{
		delete p;
	}
	list.clear();
}

void Skeleton::deinitialize()
{
	//if (m_isDeinitialized == false)
	//{
	//	delete m_imageCrawl;
	//	delete m_imageBurst;
	//	delete m_imageTransform;
	//	m_isDeinitialized = true;
	//}
}

Box Skeleton::GetBoundingBox() {
	Box box;

	box.x = x - width/2;
	box.y = y - height/2;
	box.width = width;
	box.height = height;
	box.vx = vx;
	box.vy = vy;

	return box;
}

Box Skeleton::GetBoundingBoxForApple() {
	Box box;
	switch (m_state)
	{
	case SkeletonCrawl:
		box.x = x;
		box.y = y + 25;
		box.width = 108;
		box.height = 55;
		box.vx = vx;
		box.vy = vy;
		break;
	case SkeletonTransform:
		if (m_image->getIndexFrame() == 0 || m_image->getIndexFrame() == 1 || m_image->getIndexFrame() == 2 || m_image->getIndexFrame() == 3) {
			box.x = x;
			box.y = y + 25;
			box.width = 108;
			box.height = 55;
			box.vx = vx;
			box.vy = vy;
		}
		else {
			box.x = x;
			box.y = y + 15;
			box.width = 70;
			box.height = 80;
			box.vx = vx;
			box.vy = vy;
		}
		break;
	case SkeletonBurst: case SkeletonAttact:
		box.x = 500;
		box.y = y;
		box.width = 1;
		box.height = 1;
		box.vx = vx;
		box.vy = vy;
		break;
	default:
		box.x = 500;
		box.y = y;
		box.width = 0;
		box.height = 0;
		box.vx = vx;
		box.vy = vy;
		break;
	}
	return box;
}

D3DXVECTOR2 Skeleton::getVelocity() {
	D3DXVECTOR2 result(vx, vy);
	return result;
}

void Skeleton::Update(float deltaTime) {
	m_deltaTime = deltaTime;
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
			//AttactAction();
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
	if (isUsed) {
		for (int i = 0; i < list.size(); i++)
		{
			if (list.at(i) != nullptr) {
				if (list.at(i)->getIsDead()) {
					delete list.at(i);
					list.at(i) = nullptr;
					list.erase(list.begin() + i);
				}
				else {
					list.at(i)->Update(m_deltaTime);
					list.at(i)->OnCollision(m_player, m_deltaTime);
				}
			}
		}
	}
}

void Skeleton::Draw() {
	if (!isDead) {
		m_image->Draw();
	}
	if (isUsed) {
		for (int i = 0; i < list.size(); i++) {
			if (list.at(i) != nullptr && !list.at(i)->getIsDead()) {
				list.at(i)->Draw();
			}
		}
	}
}

void Skeleton::OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime) {

}

void Skeleton::OnCollision(GameObject* colliableObject, float deltaTime) {
	if (colliableObject->getTag() == BulletAppleTag) {
		m_currentHealth = -1.0f;
		BurstAction();
	}
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
			AttactAction();
			isUsed = true;
			isDead = true;
		}
		break;
	}
	default:
		m_state = SkeletonTransform;
		m_imageTransform->Reset();
		m_image = m_imageTransform;
		m_image->setFlipHorizontal(m_isFacingRight);
		m_image->setPositionX(x);
		m_image->setPositionY(y);
		break;
	}
}

void Skeleton::BurstAction() {
	switch (m_state)
	{
	case SkeletonBurst: {
		if (m_image->getIsFinished())
			isDead = true;
		break;
	}
	default:
		m_state = SkeletonBurst;
		m_imageBurst->Reset();
		m_image = m_imageBurst;
		m_image->setPositionX(x);
		m_image->setPositionY(y + width / 4);
		break;
	}
}

void Skeleton::AttactAction() {
	switch (m_state)
	{
	case SkeletonAttact: {
		
		break;
	}
	default:
		m_state = SkeletonAttact;
		int line;
		for (line = 0; line < 16; line++) {
			BoneBullet* bone = new BoneBullet(x, y, 16, 16, line);
			list.push_back(bone);
		}
		break;
	}
}


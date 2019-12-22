#include "stdafx.h"
#include "Boss.h"

#define ANCHOR_HEALTH_BOSS 0.5
#define ATTACK_CLOSE_RANGE 30
#define HEALTH_BOSS 48

Boss::Boss(float x, float y, float width, float height, bool isFacingRight) 
	: GameObject(x, y, width, height, Tag::BossTag) 
{
	this->setIsFacingRight(isFacingRight);
	this->setPosition(D3DXVECTOR2(x, y));
	isDead = false;
	isDied = false;
	isCloseRange = false;
	isTransform = false;
	m_health = new Health(HEALTH_BOSS, HEALTH_BOSS);

	m_image;
	m_image_WarlockStanding = new Animation(L"Resources/Boss/PNG/boss-01-state_85_71_1.png", 1, 1, 1, false, 100.f);
	m_image_WarlockMagicing = new Animation(L"Resources/Boss/PNG/boss-02-state_85_71_8.png", 8, 1, 8, false, 100.f);
	m_image_CobraRenascence = new Animation(L"Resources/Boss/PNG/boss-03-state_84_87_11.png", 11, 1, 11, false, 100.f);
	m_image_CobraAttack = new Animation(L"Resources/Boss/PNG/boss-04-state_105_85_11.png", 11, 1, 11, 4, false, 80.f);
	m_image_BossDied = new Animation(L"Resources/Boss/PNG/boss-05-state-burst_85_86_15.png", 15, 1, 15, false, 100.f);

	m_image_fire0 = new Animation(L"Resources/Boss/PNG/fire-notmoving_37_53_5.png", 5, 1, 5, 0, false, 100.f);
	m_image_fire1 = new Animation(L"Resources/Boss/PNG/fire-notmoving_37_53_5.png", 5, 1, 5, 0, false, 100.f);
	m_image_fire2 = new Animation(L"Resources/Boss/PNG/fire-notmoving_37_53_5.png", 5, 1, 5, 0, false, 100.f);
	m_image_fire3 = new Animation(L"Resources/Boss/PNG/fire-notmoving_37_53_5.png", 5, 1, 5, 0, false, 100.f);

	m_state = WarlockStanding;
	m_image = m_image_WarlockStanding;
	m_image->setPositionX(this->x);
	m_image->setPositionY(this->y);
	vx = 0;
	vy = 0;
	m_startWaitStanding = GetTickCount();
}

Boss::~Boss() {
	if (m_image_WarlockMagicing != NULL) 
	{ 
		delete m_image_WarlockMagicing; 
		m_image_WarlockMagicing = nullptr; 
	}
	if (m_image_WarlockStanding != NULL) 
	{ 
		delete m_image_WarlockStanding; 
		m_image_WarlockStanding = nullptr; 
	}
	if (m_image_CobraRenascence != NULL) 
	{ 
		delete m_image_CobraRenascence; 
		m_image_CobraRenascence = nullptr; 
	}
	if (m_image_CobraAttack != NULL) 
	{ 
		delete m_image_CobraAttack; 
		m_image_CobraAttack = nullptr; 
	}
	if (m_image_BossDied != NULL) 
	{ 
		delete m_image_BossDied; 
		m_image_BossDied = nullptr; 
	}
	if (m_image_fire0 != NULL) 
	{ 
		delete m_image_fire0; 
		m_image_fire0 = nullptr; 
	}
	if (m_image_fire1 != NULL) 
	{ 
		delete m_image_fire1; 
		m_image_fire1 = nullptr; 
	}
	if (m_image_fire2 != NULL) 
	{ 
		delete m_image_fire2; 
		m_image_fire2 = nullptr; 
	}
	if (m_image_fire3 != NULL) 
	{ 
		delete m_image_fire3; 
		m_image_fire3 = nullptr; 
	}
	if (m_health != NULL) 
	{ 
		delete m_health; 
		m_health = nullptr; 
	}
}


Box Boss::GetBoundingBox() {
	Box box;
	switch (m_state)
	{
	case WarlockStanding: case WarlockMagicing:
		box.x = x;
		box.y = y;
		box.width = 85 / 2.5;
		box.height = 75;
		box.vx = vx;
		box.vy = vy;
		break;
	case CobraRenascence: case CobraAttack:
		box.x = x;
		box.y = y;
		box.width = 105 / 2.5;
		box.height = 85;
		box.vx = vx;
		box.vy = vy;
		break;
	case BossDied:
		box.x = x;
		box.y = y + height/2;
		box.width = 2;
		box.height = 2;
		box.vx = vx;
		box.vy = vy;
		break;
	default:
		break;
	}

	

	return box;
}

D3DXVECTOR2 Boss::getVelocity() {
	D3DXVECTOR2 result(vx, vy);
	return result;
}

void Boss::Update(float deltaTime) {
	if (!isDead) {
		checkHealthBoss();
		checkPositionWithPlayer();
		// update image fire
		if (isTransform) {
			m_image_fire1->Update(deltaTime);
			m_image_fire2->Update(deltaTime);
			m_image_fire3->Update(deltaTime);
		}
		// update image fire 
		if (isCloseRange) {
			m_image_fire0->Update(deltaTime);
		}

		switch (m_state)
		{
		case WarlockStanding:
			WarlockStandingAction();
			break;
		case WarlockMagicing:
			WarlockMagicingAction();
			break;
		case CobraRenascence:
			CobraRenascenceAction();
			break;
		case CobraAttack:
			CobraAttackAction();
			break;
		case BossDied:
			BossDiedAction();
			break;
		default:
			break;
		}
		// update boss
		m_image->Update(deltaTime);
		for (int i = 0; i < list.size(); i++)
		{
			if (list.at(i) != nullptr) {
				if (list.at(i)->getIsDead())
				{
					delete list.at(i);
					list.at(i) = nullptr;
					list.erase(list.begin() + i);
				}
				else {
					list.at(i)->Update(deltaTime);
					//if (list.at(i)->getTag() == StarTag)
					//	list.at(i)->attachPlayer(m_player);
				}
			}
		}
	}
}

void Boss::Draw() {
	if (!isDead) {
		m_image->Draw();
		if (isTransform && !isDied) {
			m_image_fire1->Draw();
			m_image_fire2->Draw();
			m_image_fire3->Draw();
		}
		if (isCloseRange) {
			m_image_fire0->Draw();
		}
		for (int i = 0; i < list.size(); i++)
		{
			if (list.at(i)!= nullptr) {
				list.at(i)->Draw();
			}
		}
	}
}

void Boss::OnCollision(std::map<int, GameObject*>* colliableObjects, float deltaTime) {

}

void Boss::OnCollision(GameObject* colliableObject, float deltaTime) {
	for (int i = 0; i < list.size(); i++)
	{
		if (list.at(i) != nullptr) {
			list.at(i)->OnCollision(colliableObject, deltaTime);
		}
	}

	// Todo: Refactor swich case below
	switch (colliableObject->getTag())
	{
	case BossTag:
		m_health->takeDamage(3);
		break;
	case PlayerTag:
		break;
	default:
		break;
	}
}

void Boss::attachPlayer(Player* player) {
	m_player = player;
}

void Boss::checkPositionWithPlayer() {
	float distanceX;
	if (m_player->left() <= this->left()) {
		m_isFacingRight = false;
	}
	else {
		m_isFacingRight = true;
	}

	distanceX = abs(m_player->left() - this->x);
	if (distanceX <= ATTACK_CLOSE_RANGE && isTransform == false) {
		WarlockStandingAction();
		isCloseRange = true;
	}
	else {
		if (distanceX > ATTACK_CLOSE_RANGE && isTransform == false) {
			WarlockMagicingAction();
			isCloseRange = false;
		}
	}
}

void Boss::checkHealthBoss() {
	if (m_health->getCurrentHealth() / m_health->getMaximumHealth() <= 0) {
		// boss died
		BossDiedAction();
	}
	else {
		if (m_health->getCurrentHealth() / m_health->getMaximumHealth() <= ANCHOR_HEALTH_BOSS && isTransform == false) {
			// boss use state Cobra
			CobraRenascenceAction();
			isTransform = true;
		}
	}
}

void Boss::WarlockStandingAction() {
	switch (m_state)
	{
	case WarlockStanding: {
		if (m_image->getIsFinished()) {
			// get current time
			DWORD now = GetTickCount();
			if (now - m_startWaitStanding > 3000)
			{
				// change animation
				WarlockMagicingAction();
			}
		}
		if (isCloseRange)
			setPositionFireAladdin();
		m_image->setFlipHorizontal(!m_isFacingRight);
		break;
	}
	default:
		m_state = WarlockStanding;
		m_image_WarlockStanding->Reset();
		m_image = m_image_WarlockStanding;
		m_image->setFlipHorizontal(!m_isFacingRight);
		vx = 0;
		vy = 0;
		m_image->setPositionX(x);
		m_image->setPositionY(y);
		// reset start marking time
		m_startWaitStanding = GetTickCount();
		if (isCloseRange)
			setPositionFireAladdin();
		break;
	}
}

void Boss::WarlockMagicingAction() {
	switch (m_state)
	{
	case WarlockMagicing: {
		if (m_image->getIsFinished()) {
			DWORD now1 = GetTickCount();
			if (now1 - m_WaitCreateStar > 300) {
				createStar(); 
				m_WaitCreateStar = GetTickCount();
			}

			DWORD now = GetTickCount();
			if (now - m_startWaitMagicing > 5000)
			{
				// change animation
				WarlockStandingAction();
			}
		}
		m_image->setFlipHorizontal(!m_isFacingRight);
		break;
	}
	default:
		m_state = WarlockMagicing;
		m_image_WarlockMagicing->Reset();
		m_image = m_image_WarlockMagicing;
		m_image->setFlipHorizontal(!m_isFacingRight);
		vx = 0;
		vy = 0;
		m_image->setPositionX(x);
		m_image->setPositionY(y);
		m_startWaitMagicing = GetTickCount();
		m_WaitCreateStar = GetTickCount();
		break;
	}
}

void Boss::CobraRenascenceAction() {
	switch (m_state)
	{
	case CobraRenascence: {
		if (m_image->getIsFinished()) {
			// get current time
			DWORD now = GetTickCount();
			if (now - m_startWaitStanding > 2000)
			{
				// change animation
				CobraAttackAction();
			}
		}
		m_image->setFlipHorizontal(!m_isFacingRight);
		vx = 0;
		vy = 0;
		m_image->setPositionX(x);
		m_image->setPositionY(y);
		setPositionFire();
		break;
	}
	default:
		m_state = CobraRenascence;
		m_image_CobraRenascence->Reset();
		m_image_CobraRenascence->setFlipHorizontal(!m_isFacingRight);
		m_image = m_image_CobraRenascence;
		vx = 0;
		vy = 0;
		m_image->setPositionX(x);
		m_image->setPositionY(y);
		setPositionFire();
		m_startWaitStanding = GetTickCount();
		break;
	}
}

void Boss::CobraAttackAction() {
	switch (m_state)
	{
	case CobraAttack: {
		if (m_image->getIndexFrame()==2) {
			createFire();
		}
		if (m_image->getIsFinished()) {
			DWORD now = GetTickCount();
			if (now - m_startWaitAttack > 2500)
			{
				m_image->Reset();
				// reset start marking time
				m_startWaitAttack = GetTickCount();
			}
		}
		m_image->setFlipHorizontal(!m_isFacingRight);
		setPositionFire();
		break;
	}
	default:
		m_state = CobraAttack;
		m_image_CobraAttack->Reset();
		m_image = m_image_CobraAttack;
		m_image->setFlipHorizontal(!m_isFacingRight);
		vx = 0;
		vy = 0;
		m_image->setPositionX(x);
		m_image->setPositionY(y);
		m_startWaitAttack = GetTickCount();
		setPositionFire();
		break;
	}
}

void Boss::BossDiedAction() {
	switch (m_state)
	{
	case BossDied: {
		if (m_image->getIsFinished()) {
			isDead = true;
		}
		break;
	}
	default:
		m_state = BossDied;
		m_image_BossDied->Reset();
		m_image = m_image_BossDied;
		vx = 0;
		vy = 0;
		m_image->setPositionX(x);
		m_image->setPositionY(y);
		isDied = true;
		break;
	}
}

void Boss::createStar() {
	Star* star = new Star(x, y, 28, 16, this);
	star->attachPlayer(m_player);
	list.push_back(star);
}

void Boss::createFire() {
	Fire* fire = new Fire(x, y, 28, 16, this);
	//fire->attachPlayer(m_player);
	list.push_back(fire);
}

int Boss::randomPostionFire(bool type) {
	// true == x || false == y
	int result;
	if (type) {
		result = rand() % 70 + int(this->left() - 40);
	}
	else {
		result = rand() % 10 + int(this->top() + 10);
	}
	return result;
}

void Boss::setPositionFire() {
	if (m_image_fire1->getIsFinished()) {
		m_image_fire1->Reset();
		m_image_fire1->setFlipHorizontal(!m_isFacingRight);
		m_image_fire1->setPositionX(randomPostionFire(true));
		m_image_fire1->setPositionY(randomPostionFire(false));
	}

	if (m_image_fire2->getIsFinished()) {
		m_image_fire2->Reset();
		m_image_fire2->setFlipHorizontal(!m_isFacingRight);
		m_image_fire2->setPositionX(randomPostionFire(true));
		m_image_fire2->setPositionY(randomPostionFire(false));
	}

	if (m_image_fire3->getIsFinished()) {
		m_image_fire3->Reset();
		m_image_fire3->setFlipHorizontal(!m_isFacingRight);
		m_image_fire3->setPositionX(randomPostionFire(true));
		m_image_fire3->setPositionY(randomPostionFire(false));
	}
}

void Boss::setPositionFireAladdin() {
	if (m_image_fire0->getIsFinished()) {
		m_image_fire0->Reset();
	}
	m_image_fire0->setPositionX(m_player->getPosition().x);
	m_image_fire0->setPositionY(m_player->getPosition().y + 10);
}

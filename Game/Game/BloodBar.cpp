#include "stdafx.h"
#include "BloodBar.h"

BloodBar::BloodBar(float x, float y, float width, float height) : GameObject(x, y, width, height, Tag::BloodBarTag)  {

	m_imageHealth1 = new Animation(L"Resources/Items/PNG/BloodBar7_120_30_4.png", 4, 1, 4, true, 200.f);
	m_imageHealth2 = new Animation(L"Resources/Items/PNG/BloodBar6_120_30_8.png", 8, 1, 8, true, 200.f);
	m_imageHealth3 = new Animation(L"Resources/Items/PNG/BloodBar5_120_30_6.png", 6, 1, 6, true, 200.f);
	m_imageHealth4 = new Animation(L"Resources/Items/PNG/BloodBar4_120_30_4.png", 4, 1, 4, true, 100.f);
	m_imageHealth5 = new Animation(L"Resources/Items/PNG/BloodBar3_120_30_4.png", 4, 1, 4, true, 100.f);
	m_imageHealth7 = new Animation(L"Resources/Items/PNG/BloodBar2_120_30_4.png", 4, 1, 4, true, 100.f);
	m_imageHealth9 = new Animation(L"Resources/Items/PNG/BloodBar1_120_30_4.png", 4, 1, 4, true, 100.f);

	m_image = m_imageHealth9;
	m_image->setPositionX(x);
	m_image->setPositionY(y);
	vx = vy = 0;
}

BloodBar::~BloodBar() {
	if (m_imageHealth1 != NULL) { delete m_imageHealth1 ; m_imageHealth1 = nullptr; }
	if (m_imageHealth2 != NULL) { delete m_imageHealth2; m_imageHealth2 = nullptr; }
	if (m_imageHealth3 != NULL) { delete m_imageHealth3; m_imageHealth3 = nullptr; }
	if (m_imageHealth4 != NULL) { delete m_imageHealth4; m_imageHealth4 = nullptr; }
	if (m_imageHealth5 != NULL) { delete m_imageHealth5; m_imageHealth5 = nullptr; }
	if (m_imageHealth7 != NULL) { delete m_imageHealth7; m_imageHealth7 = nullptr; }
	if (m_imageHealth9 != NULL) { delete m_imageHealth9; m_imageHealth9 = nullptr; }
}

void BloodBar::Update(float deltaTime) {
	changeImage();
	if (healthCurrent >= 0)
		m_image->Update(deltaTime);
}

void BloodBar::Draw() {
	if (healthCurrent >= 0)
		m_image->DrawOnScreen();
}

void BloodBar::changeImage() {
	
	if (m_player == NULL) {
		healthCurrent = -1;
		return;
	}

	// get health current player
	healthCurrent = (int)m_player->getCurrentHealth();

	switch (healthCurrent)
	{
	case 9: case 8:
		m_image = m_imageHealth9;
		break;
	case 6: case 7:
		m_image = m_imageHealth7;
		break;
	case 5:
		m_image = m_imageHealth5;
		break;
	case 4:
		m_image = m_imageHealth4;
		break;
	case 3:
		m_image = m_imageHealth3;
		break;
	case 2:
		m_image = m_imageHealth2;
		break;
	case 1:
		m_image = m_imageHealth1;
		break;
	default:
		m_image = m_imageHealth9;
		break;
	}
	m_image->setPositionX(x);
	m_image->setPositionY(y);
}

void BloodBar::attachPlayer(Player* player) {
	m_player = player;
}

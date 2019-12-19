#include "stdafx.h"
#include "LifeScores.h"

LifeScores::LifeScores(float x, float y, float width, float height) : GameObject(x, y, width, height, Tag::ScoresTag) {
	ischange = false;
	currentScores = 3;
	//test = 0;

	// icon life
	m_imageIcon = new Animation(L"Resources/Items/life-aladdin-icon2.png", 1, 1, 1);
	m_imageIcon->setPositionX(x);
	m_imageIcon->setPositionY(y);

	m_imageScore = new Animation(L"Resources/Items/PNG/number-font-1/number0-9.png", 10, 1, 10, 0, false, 500.f);
	m_imageScore->setPositionX(x + 15);
	m_imageScore->setPositionY(y);
}

LifeScores::~LifeScores() {
	if (m_imageIcon != NULL) { delete m_imageIcon; m_imageIcon = nullptr; }
	if (m_imageScore != NULL) { delete m_imageScore; m_imageScore = nullptr; }
}

void LifeScores::Update(float deltaTime) {
	if (!ischange) {
		changeDisplayScores();
		ischange = true;
	}
	//test
	/*test += 1;
	if (test > 10000)
		test = 1;

	if (test % 50 == 0)
		abstractScores();*/
}

void LifeScores::Draw() {
	
	if (currentScores >= 0) {
		m_imageIcon->DrawOnScreen();
		m_imageScore->DrawOnScreen();
	}
}

void LifeScores::increaseScores() {
	currentScores++;
	changeDisplayScores();
}

void LifeScores::abstractScores() {
	currentScores--;
	changeDisplayScores();
}

int LifeScores::getScore() {
	return currentScores;
}

void LifeScores::changeDisplayScores() {
	if (currentScores > 9)
		currentScores = 9;
	if (currentScores < 0)
		m_imageScore->setIndexFrame(0);
	m_imageScore->setIndexFrame(currentScores);
}

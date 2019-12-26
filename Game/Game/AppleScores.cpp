#include "stdafx.h"
#include "AppleScores.h"

AppleScores::AppleScores(float x, float y, float width, float height) : GameObject(x, y, width, height, Tag::ScoresTag) {
	ischange = false;
	currentScores = 10;
	//test = 0;

	// icon Apple
	m_imageIcon = new Animation(L"Resources/Items/apple.png", 1, 1, 1);
	m_imageIcon->setPositionX(x);
	m_imageIcon->setPositionY(y);

	m_imageOne = new Animation(L"Resources/Items/PNG/number-font-1/number0-9.png", 10, 1, 10, 0, false, 500.f);
	m_imageTen = new Animation(L"Resources/Items/PNG/number-font-1/number0-9.png", 10, 1, 10, 0, false, 500.f);
	m_imageHundred = new Animation(L"Resources/Items/PNG/number-font-1/number0-9.png", 10, 1, 10, 0, false, 500.f);
}

AppleScores::~AppleScores() {
	if (m_imageIcon != NULL) { delete m_imageIcon; m_imageIcon = nullptr; }
	if (m_imageOne != NULL) { delete m_imageOne; m_imageOne = nullptr; }
	if (m_imageTen != NULL) { delete m_imageTen; m_imageTen = nullptr; }
	if (m_imageHundred != NULL) { delete m_imageHundred; m_imageHundred = nullptr; }
}

void AppleScores::Update(float deltaTime) {
	if (m_player->m_appleCount != currentScores)
	{
		changeDisplayScores();
	}

	//test
	/*if (currentScores < 999)
	{
		test += 1;
		if (test % 15 == 0) {
			increaseScores();
		}
	}*/
}

void AppleScores::Draw() {
	m_imageIcon->DrawOnScreen();
	if (currentScores >= 100) {

		m_imageOne->setPositionX(x + 35);
		m_imageOne->setPositionY(y);

		m_imageTen->setPositionX(x + 25);
		m_imageTen->setPositionY(y);

		m_imageHundred->setPositionX(x + 15);
		m_imageHundred->setPositionY(y);

		m_imageHundred->DrawOnScreen();
		m_imageOne->DrawOnScreen();
		m_imageTen->DrawOnScreen();
	}
	else {
		if (currentScores >= 10) {
			m_imageOne->setPositionX(x + 25);
			m_imageOne->setPositionY(y);

			m_imageTen->setPositionX(x + 15);
			m_imageTen->setPositionY(y);

			m_imageOne->DrawOnScreen();
			m_imageTen->DrawOnScreen();
		}
		else {
			m_imageOne->setPositionX(x + 15);
			m_imageOne->setPositionY(y);

			m_imageOne->DrawOnScreen();
		}
	}
}

void AppleScores::attachPlayer(Player * player)
{
	m_player = player;
}

void AppleScores::increaseScores() {
	currentScores++;
	changeDisplayScores();
}

void AppleScores::abstractScores() {
	currentScores--;
	changeDisplayScores();
}

void AppleScores::resetLifeAladdin() {
	currentScores = 10;
	changeDisplayScores();
}

int AppleScores::getScore() {
	return currentScores;
}

void AppleScores::setScore(int value)
{
	currentScores = value;
	changeDisplayScores();
}

void AppleScores::changeDisplayScores() {
	currentScores = m_player->m_appleCount;
	int hundred, ten, one, remainder;

	hundred = currentScores / 100;
	remainder = currentScores % 100;
	ten = remainder / 10;
	one = remainder % 10;

	m_imageHundred->setIndexFrame(hundred);
	m_imageTen->setIndexFrame(ten);
	m_imageOne->setIndexFrame(one);

}

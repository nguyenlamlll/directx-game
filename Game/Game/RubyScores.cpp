#include "stdafx.h"
#include "RubyScores.h"

RubyScores::RubyScores(float x, float y, float width, float height) : GameObject(x, y, width, height, Tag::ScoresTag) {

	currentScores = 0;
	//test = 0;

	// icon Ruby
	m_imageIcon = new Animation(L"Resources/Items/ruby.png", 1, 1, 1);
	m_imageIcon->setPositionX(x);
	m_imageIcon->setPositionY(y);

	m_imageOne = new Animation(L"Resources/Items/PNG/number-font-1/number0-9.png", 10, 1, 10, 0, false, 500.f);
	m_imageTen = new Animation(L"Resources/Items/PNG/number-font-1/number0-9.png", 10, 1, 10, 0, false, 500.f);
	m_imageHundred = new Animation(L"Resources/Items/PNG/number-font-1/number0-9.png", 10, 1, 10, 0, false, 500.f);
}

RubyScores::~RubyScores() {
	if (m_imageIcon != NULL) { delete m_imageIcon; m_imageIcon = nullptr; }
	if (m_imageOne != NULL) { delete m_imageOne; m_imageOne = nullptr; }
	if (m_imageTen != NULL) { delete m_imageTen; m_imageTen = nullptr; }
	if (m_imageHundred != NULL) { delete m_imageHundred; m_imageHundred = nullptr; }
}

void RubyScores::Update(float deltaTime) {
	//test

	/*if (currentScores < 999)
	{
		test += 1;
		if (test % 15 == 0) {
			increaseScores();
		}
	}*/
}

void RubyScores::Draw() {
	if (currentScores > 0) {
		m_imageIcon->DrawOnScreen();
		if (currentScores >= 100) {

			m_imageOne->setPositionX(x + 40);
			m_imageOne->setPositionY(y);

			m_imageTen->setPositionX(x + 30);
			m_imageTen->setPositionY(y);

			m_imageHundred->setPositionX(x + 20);
			m_imageHundred->setPositionY(y);

			m_imageHundred->DrawOnScreen();
			m_imageOne->DrawOnScreen();
			m_imageTen->DrawOnScreen();
		}
		else {
			if (currentScores >= 10) {
				m_imageOne->setPositionX(x + 30);
				m_imageOne->setPositionY(y);

				m_imageTen->setPositionX(x + 20);
				m_imageTen->setPositionY(y);

				m_imageOne->DrawOnScreen();
				m_imageTen->DrawOnScreen();
			}
			else {
				m_imageOne->setPositionX(x + 20);
				m_imageOne->setPositionY(y);

				m_imageOne->DrawOnScreen();
			}
		}
	}
}

void RubyScores::increaseScores() {
	currentScores += 1;
	changeDisplayScores();
}

void RubyScores::abstractScores(int value) {
	currentScores -= value;
	changeDisplayScores();
}

void RubyScores::changeDisplayScores() {
	int hundred, ten, one, remainder;
	
	hundred = currentScores / 100;
	remainder = currentScores % 100;
	ten = remainder / 10;
	one = remainder % 10;
	
	m_imageHundred->setIndexFrame(hundred);
	m_imageTen->setIndexFrame(ten);
	m_imageOne->setIndexFrame(one);
}

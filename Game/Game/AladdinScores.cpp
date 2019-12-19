#include "stdafx.h"#include "stdafx.h"
#include "AladdinScores.h"

AladdinScores::AladdinScores(float x, float y, float width, float height) : GameObject(x, y, width, height, Tag::ScoresTag) {
	currentScores = 0;
	changing = changeTen = changeHundred = changeThousand = false;
	//test = 0;

	// icon Apple 
	m_imageOne = new Animation(L"Resources/Items/PNG/number-font-2/font-2-number0-9.png", 10, 1, 10, 0, false, 100.f);
	m_imageTen = new Animation(L"Resources/Items/PNG/number-font-2/font-2-number0-9.png", 10, 1, 10, 0, false, 50.f);
	m_imageHundred = new Animation(L"Resources/Items/PNG/number-font-2/font-2-number0-9.png", 10, 1, 10, 0, false, 100.f);
	m_imageThousand= new Animation(L"Resources/Items/PNG/number-font-2/font-2-number0-9.png", 10, 1, 10, 0, false, 200.f);
	m_imageTenThousand = new Animation(L"Resources/Items/PNG/number-font-2/font-2-number0-9.png", 10, 1, 10, 0, false, 400.f);

	m_imageOne->setPositionX(x);
	m_imageOne->setPositionY(y);
}

AladdinScores::~AladdinScores() {
	if (m_imageOne != NULL) { delete m_imageOne; m_imageOne = nullptr; }
	if (m_imageTen != NULL) { delete m_imageTen; m_imageTen = nullptr; }
	if (m_imageHundred != NULL) { delete m_imageHundred; m_imageHundred = nullptr; }
	if (m_imageThousand != NULL) { delete m_imageThousand; m_imageThousand = nullptr; }
	if (m_imageTenThousand != NULL) { delete m_imageTenThousand; m_imageTenThousand = nullptr; }
}

void AladdinScores::Update(float deltaTime) {
	if (changing)
	{
		styleBeforeChange();
		m_imageTen->Update(deltaTime);
		m_imageHundred->Update(deltaTime);
		m_imageThousand->Update(deltaTime);
	}
	//test
	//if (currentScores < 99999)
	//{
	//	test += 1;
	//	if (test % 50 == 0) {
	//		increaseScores(250);
	//	}
	//	/*else if (test % 211 == 0) {
	//		increaseAladdinScores(250);
	//	}*/
	//}
}

void AladdinScores::Draw() {
	if (currentScores > 0) {
		if (currentScores >= 10000) {

			m_imageTen->setPositionX(x - 18);
			m_imageTen->setPositionY(y);

			m_imageHundred->setPositionX(x - 36);
			m_imageHundred->setPositionY(y);

			m_imageThousand->setPositionX(x - 54);
			m_imageThousand->setPositionY(y);

			m_imageTenThousand->setPositionX(x - 72);
			m_imageTenThousand->setPositionY(y);

			m_imageOne->DrawOnScreen();
			m_imageTen->DrawOnScreen();
			m_imageHundred->DrawOnScreen();
			m_imageThousand->DrawOnScreen();
			m_imageTenThousand->DrawOnScreen();
		}
		else {
			if (currentScores >= 1000) {
				m_imageTen->setPositionX(x - 18);
				m_imageTen->setPositionY(y);

				m_imageHundred->setPositionX(x - 36);
				m_imageHundred->setPositionY(y);

				m_imageThousand->setPositionX(x - 54);
				m_imageThousand->setPositionY(y);

				m_imageOne->DrawOnScreen();
				m_imageTen->DrawOnScreen();
				m_imageHundred->DrawOnScreen();
				m_imageThousand->DrawOnScreen();
			}
			else {
				m_imageTen->setPositionX(x - 18);
				m_imageTen->setPositionY(y);

				m_imageHundred->setPositionX(x - 36);
				m_imageHundred->setPositionY(y);

				m_imageOne->DrawOnScreen();
				m_imageTen->DrawOnScreen();
				m_imageHundred->DrawOnScreen();
			}
		}
	}
}

void AladdinScores::increaseScores(int value) {
	// face 250
	// health 150
	// ruby 150
	currentScores += value;
	setNumberScores();
	changing = true;
}

void AladdinScores::styleBeforeChange() {
	if (m_imageTen->getIsFinished()) {
		m_imageTen->Reset();
	}
	if (m_imageTen->getIndexFrame() == ten ) {
		changeTen = true;
	}
	if (m_imageHundred->getIsFinished()) {
		m_imageHundred->Reset();
	}
	if (m_imageHundred->getIndexFrame() == hundred) {
		changeHundred = true;
	}
	if (m_imageThousand->getIsFinished()) {
		m_imageThousand->Reset();
	}
	if (m_imageThousand->getIndexFrame() == thousand) {
		changeThousand = true;
	}

	if (changeThousand && changeHundred && changeTen) {
		changing = false;
		changeThousand = changeHundred = changeTen = false;
		changeDisplayScores();
	}

}

void AladdinScores::changeDisplayScores() {

	m_imageOne->setIndexFrame(one);
	m_imageTen->setIndexFrame(ten);
	m_imageHundred->setIndexFrame(hundred);
	m_imageThousand->setIndexFrame(thousand);
	m_imageTenThousand->setIndexFrame(tenThousand);
}

void AladdinScores::setNumberScores() {
	int remainder;
	tenThousand = currentScores / 10000;
	remainder = currentScores % 10000;
	thousand = remainder / 1000;
	remainder = remainder % 1000;
	hundred = remainder / 100;
	remainder = remainder % 100;
	ten = remainder / 10;
	one = remainder % 10;
}

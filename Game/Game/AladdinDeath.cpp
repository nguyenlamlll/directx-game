#include "stdafx.h"
#include "AladdinDeath.h"


AladdinDeath::AladdinDeath()
{
	m_background = new Sprite(L"Resources/black.png");
	m_background->setPositionX(Global::GetInstance()->g_ScreenWidth / 2);
	m_background->setPositionY(Global::GetInstance()->g_ScreenHeight / 2);
	m_animation = new Animation(L"Resources/AladdinState/PNG/AladdinDiedWithGenie_15.png", 15, 1, 15, false, 40.f);
	m_animation->Reset();
	m_animation->setPositionX(Global::GetInstance()->g_ScreenWidth / 2 + 25);
	m_animation->setPositionY(Global::GetInstance()->g_ScreenHeight / 2);
}


AladdinDeath::~AladdinDeath()
{
	delete m_background;
	delete m_animation;
}

void AladdinDeath::reset()
{
	m_animation->Reset();
	m_boxingBellPlayCount = 0;
}

void AladdinDeath::Update(float deltaTime)
{
	m_animation->Update(deltaTime);

	if (m_boxingBellPlayCount <= 2)
	{
		if (m_timer >= 200)
		{
			Sound::getInstance()->play(SoundNames::RESTART_LIFE_SOUND, false);
			m_boxingBellPlayCount += 1;
			m_timer -= m_timer;
		}
		else
		{
			m_timer += deltaTime;
		}
	}
}

void AladdinDeath::Draw()
{
	m_background->DrawOnScreen();
	m_animation->DrawOnScreen();
}

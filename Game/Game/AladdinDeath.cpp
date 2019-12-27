#include "stdafx.h"
#include "AladdinDeath.h"


AladdinDeath::AladdinDeath()
{
	isChange = false;
	m_background = new Sprite(L"Resources/black.png");
	m_background->setPositionX(Global::GetInstance()->g_ScreenWidth / 2);
	m_background->setPositionY(Global::GetInstance()->g_ScreenHeight / 2);
	m_animation_aladdinDied = new Animation(L"Resources/AladdinState/PNG/AladdinDied_13.png", 13, 1, 13, false, 80.f);
	m_animation_aladdinDiedWithGenie = new Animation(L"Resources/AladdinState/PNG/AladdinDiedWithGenie_15.png", 15, 1, 15, false, 80.f);
	m_animation_monkey = new Animation(L"Resources/AladdinState/PNG/monkey-aladdin-dead-6.png", 6, 1, 6, true, 80.f);
	m_animation = m_animation_aladdinDied;
	m_animation->Reset();
	m_animation->setPositionX(Global::GetInstance()->g_ScreenWidth / 2 + 25);
	m_animation->setPositionY(Global::GetInstance()->g_ScreenHeight / 2);

	m_animation_monkey->setPositionX(Global::GetInstance()->g_ScreenWidth / 2 + 85);
	m_animation_monkey->setPositionY(Global::GetInstance()->g_ScreenHeight / 2 + 30);
}


AladdinDeath::~AladdinDeath()
{
	delete m_background;
	delete m_animation_aladdinDied;
	delete m_animation_aladdinDiedWithGenie;
	delete m_animation_monkey;
}

void AladdinDeath::reset()
{
	m_animation_aladdinDied->Reset();
	m_animation = m_animation_aladdinDied;
	isChange = false;
	m_animation_monkey->Reset();
	m_boxingBellPlayCount = 0;
}

void AladdinDeath::Update(float deltaTime)
{
	if (!isChange && m_animation->getIsFinished()) {
		m_animation = m_animation_aladdinDiedWithGenie;
		m_animation->Reset();
		m_animation->setPositionX(Global::GetInstance()->g_ScreenWidth / 2 + 25);
		m_animation->setPositionY(Global::GetInstance()->g_ScreenHeight / 2);
	}
	m_animation->Update(deltaTime);
	m_animation_monkey->Update(deltaTime);

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
	m_animation_monkey->DrawOnScreen();
}

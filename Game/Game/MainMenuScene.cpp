#include "stdafx.h"
#include "MainMenuScene.h"
#include "Global.h"

MainMenuScene::MainMenuScene()
{
	m_background = new Sprite(L"Resources/menu.png");
	m_background->setPositionX(Global::GetInstance()->g_ScreenWidth / 2);
	m_background->setPositionY(Global::GetInstance()->g_ScreenHeight / 2);

	m_gameLogo = new Sprite(L"Resources/title.png");
	m_gameLogo->setPositionX(Global::GetInstance()->g_ScreenWidth / 2);
	m_gameLogo->setPositionY(Global::GetInstance()->g_ScreenHeight / 2 + 40);
	RECT rect;
	SetRect(&rect, (int)0, (int)0, (int)322, (int)100);
	m_gameLogo->setSourceRect(rect);

	m_selectionSword = new Sprite(L"Resources/menu_select.png");
	m_selectionSword->setPositionX(Global::GetInstance()->g_ScreenWidth / 2 - 80);
	m_selectionSword->setPositionY(Global::GetInstance()->g_ScreenHeight / 2);

	auto textPosition = D3DXVECTOR2(Global::GetInstance()->g_ScreenWidth / 2 - 50, Global::GetInstance()->g_ScreenHeight / 2 - 10);
	m_playText = new Text(L"PRESS START", L"Arial", 18, textPosition, D3DCOLOR_ARGB(255, 255, 255, 255), false, true);

	textPosition = D3DXVECTOR2(Global::GetInstance()->g_ScreenWidth / 2 - 50, Global::GetInstance()->g_ScreenHeight / 2 + 20);
	m_optionsText = new Text(L"OPTIONS", L"Arial", 18, textPosition, D3DCOLOR_ARGB(255, 255, 255, 255), false, true);
}

void MainMenuScene::initialize()
{
	Sound::getInstance()->play(SoundNames::MAIN_MENU_SOUD, true);
	Sound::getInstance()->setVolume(100, SoundNames::MAIN_MENU_SOUD);
}

MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::Update(float deltaTime)
{
	if (KeyboardInput::GetInstance()->isKeyTriggered(VK_RETURN))
	{
		if (m_selectionIndex == 1)
		{
			SceneManager::getInstance()->changeScene(new DungeonScene());
			return;
		}
	}

	if (KeyboardInput::GetInstance()->isKeyTriggered(VK_DOWN))
	{
		if (m_selectionIndex == 1)
		{
			m_selectionIndex = 2;
		}
		else {
			m_selectionIndex = 1;
		}
	}
	if (KeyboardInput::GetInstance()->isKeyTriggered(VK_UP))
	{
		if (m_selectionIndex == 1)
		{
			m_selectionIndex = 2;
		}
		else {
			m_selectionIndex = 1;
		}
	}

	if (m_selectionIndex == 1)
	{
		m_selectionSword->setPositionX(Global::GetInstance()->g_ScreenWidth / 2 - 80);
		m_selectionSword->setPositionY(Global::GetInstance()->g_ScreenHeight / 2);
	}
	if (m_selectionIndex == 2)
	{
		m_selectionSword->setPositionX(Global::GetInstance()->g_ScreenWidth / 2 - 80);
		m_selectionSword->setPositionY(Global::GetInstance()->g_ScreenHeight / 2 + 30);
	}

}

void MainMenuScene::Draw()
{
	m_background->DrawOnScreen();

	m_gameLogo->DrawOnScreen();
	m_selectionSword->DrawOnScreen();
	m_playText->draw();
	m_optionsText->draw();
}

void MainMenuScene::OnKeyDown(int keyCode)
{
}

void MainMenuScene::OnKeyUp(int keyCode)
{
}

void MainMenuScene::ReleaseAll()
{
	delete m_background;
	delete m_gameLogo;
	delete m_selectionSword;
	delete m_playText;
	delete m_optionsText;

	Sound::getInstance()->stop(SoundNames::MAIN_MENU_SOUD);
}

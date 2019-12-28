#include "stdafx.h"
#include "LevelCompleteScene.h"


LevelCompleteScene::LevelCompleteScene(Scene* nextScene)
{
	pXM = Global::GetInstance()->g_ScreenWidth / 2 + 120;
	pYM = Global::GetInstance()->g_ScreenHeight / 2 + 140;
	pXA = pXM + 50;
	pYA = pYM - 10;
	m_levelComplete = new Sprite(L"Resources/title.png");
	m_levelComplete->setPositionX(Global::GetInstance()->g_ScreenWidth / 2);
	m_levelComplete->setPositionY(Global::GetInstance()->g_ScreenHeight / 2 + 40);
	m_monkeyMoving = new Animation(L"Resources/AladdinState/PNG/monkey-moving-complete_8.png", 8, 1, 8, true, 40.f);
	m_monkeyMoving->setPositionX(pXM);
	m_monkeyMoving->setPositionY(pYM);
	m_aladdinMoving = new Animation(L"Resources/AladdinState/PNG/AladdinWin_8.png", 8, 1, 8, true, 60.f);
	m_aladdinMoving->setPositionX(pXA);
	m_aladdinMoving->setPositionY(pYA);
	RECT rect;
	SetRect(&rect, (int)0, (int)100, (int)322, (int)150 + 110);
	m_levelComplete->setSourceRect(rect);
	m_nextScene = nextScene;

	start = GetTickCount();
}

void LevelCompleteScene::initialize()
{
	Sound::getInstance()->play(SoundNames::LEVEL_COMPLETE_SOUD, false);
}

LevelCompleteScene::~LevelCompleteScene()
{
}

void LevelCompleteScene::ReleaseAll()
{
	delete m_levelComplete;
	delete m_monkeyMoving;
	delete m_aladdinMoving;
	Sound::getInstance()->stop(SoundNames::LEVEL_COMPLETE_SOUD);
}

void LevelCompleteScene::Update(float deltaTime)
{
	auto now = GetTickCount();
	auto dt = now - start;
	if (dt > 4500)
	{
		m_isAnimationFinished = true;
		start = GetTickCount();
	}

	if (m_isAnimationFinished)
	{
		SceneManager::getInstance()->changeScene(m_nextScene);
		return;
	}
	m_monkeyMoving->Update(deltaTime);
	if(pXM>0)
		pXM -= 2.5f;
	m_monkeyMoving->setPositionX(pXM);
	m_monkeyMoving->setPositionY(pYM);

	m_aladdinMoving->Update(deltaTime);
	if(pXA > 0)
		pXA -= 2.5f;
	m_aladdinMoving->setPositionX(pXA);
	m_aladdinMoving->setPositionY(pYA);

}

void LevelCompleteScene::Draw()
{
	m_levelComplete->DrawOnScreen();
	m_monkeyMoving->DrawOnScreen();
	m_aladdinMoving->DrawOnScreen();
}

void LevelCompleteScene::OnKeyDown(int keyCode)
{
}

void LevelCompleteScene::OnKeyUp(int keyCode)
{
}
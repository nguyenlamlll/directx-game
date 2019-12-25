#include "stdafx.h"
#include "LevelCompleteScene.h"


LevelCompleteScene::LevelCompleteScene(Scene* nextScene)
{
	m_levelComplete = new Sprite(L"Resources/title.png");
	m_levelComplete->setPositionX(Global::GetInstance()->g_ScreenWidth / 2);
	m_levelComplete->setPositionY(Global::GetInstance()->g_ScreenHeight / 2 + 40);
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
}

void LevelCompleteScene::Draw()
{
	m_levelComplete->DrawOnScreen();
}

void LevelCompleteScene::OnKeyDown(int keyCode)
{
}

void LevelCompleteScene::OnKeyUp(int keyCode)
{
}

void LevelCompleteScene::ReleaseAll()
{
	delete m_levelComplete;
	Sound::getInstance()->stop(SoundNames::LEVEL_COMPLETE_SOUD);
}


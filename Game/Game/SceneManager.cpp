#include "stdafx.h"
#include "SceneManager.h"

SceneManager* SceneManager::instance = nullptr;
SceneManager * SceneManager::getInstance()
{
	if (instance)
	{
		return instance;
	}
	else
	{
		instance = new SceneManager();
		return instance;
	}
}

SceneManager::~SceneManager()
{
}

Scene * SceneManager::getCurrentScene()
{
	return m_currentScene;
}

void SceneManager::changeScene(Scene * newScene)
{
	if (m_currentScene)
	{
		m_currentScene->ReleaseAll();
		delete m_currentScene;
		m_currentScene = nullptr;
	}
	m_currentScene = newScene;
}

#pragma once
#include "Scene.h"

class SceneManager
{
private:
	static SceneManager* instance;
	Scene* m_currentScene = nullptr;
public:
	static SceneManager* getInstance();
	~SceneManager();

	Scene* getCurrentScene();
	void changeScene(Scene* newScene);

};


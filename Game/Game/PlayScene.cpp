#include "stdafx.h"
#include "PlayScene.h"

#define BRICK_TEXTURE_PATH L"brick.png"
#define PAD_TEXTURE_PATH L"Resources\\pad.png"
#define BALL_TEXTURE_PATH L"Resources\\ball.png"
#define PLAYER_TEXTURE_PATH L"Resources\\player.png"

#define SCREEN_WIDTH Global::GetInstance()->g_ScreenWidth
#define SCREEN_HEIGHT Global::GetInstance()->g_ScreenHeight

PlayScene::PlayScene()
{
	loadResources();
}


PlayScene::~PlayScene()
{
}

void PlayScene::Update(float deltaTime)
{
	auto visibleObjects = m_grid->getVisibleObjects();
	for (auto it = visibleObjects->begin(); it != visibleObjects->end(); it++)
	{
		it->second->Update(deltaTime);
	}

	m_player->Update(deltaTime);
	auto playerPosition = m_grid->calculateObjectPositionOnGrid(m_player);
	m_grid->getCollidableObjects(m_listCanCollideWithPlayer, playerPosition.x, playerPosition.y);
	m_player->OnCollision(m_listCanCollideWithPlayer, deltaTime);
}

void PlayScene::Draw()
{
	auto visibleObjects = m_grid->getVisibleObjects();
	for (auto it = visibleObjects->begin(); it != visibleObjects->end(); it++)
	{
		it->second->Draw();
	}
	m_player->Draw();
}

void PlayScene::OnKeyDown(int keyCode)
{
}

void PlayScene::OnKeyUp(int keyCode)
{
}

void PlayScene::ReleaseAll()
{
}

void PlayScene::loadResources()
{
	auto m_ball = new Ball(
		SCREEN_WIDTH / 2 + 50,
		SCREEN_HEIGHT / 2,
		22.f,
		22.f,
		BALL_TEXTURE_PATH);

	auto m_leftPad = new Pad(
		20,
		SCREEN_HEIGHT / 2,
		43.f,
		89.f,
		PAD_TEXTURE_PATH
	);
	m_leftPad->SetControlDevice(ControlDevice::None);

	auto m_rightPad = new Pad(
		SCREEN_WIDTH - 50,
		SCREEN_HEIGHT / 2,
		43.f,
		89.f,
		PAD_TEXTURE_PATH
	);
	m_rightPad->SetControlDevice(ControlDevice::None);

	auto m_pad03 = new Pad(
		SCREEN_WIDTH + 150,
		SCREEN_HEIGHT / 2 + 50,
		43.f,
		89.f,
		PAD_TEXTURE_PATH
	);
	m_pad03->SetControlDevice(ControlDevice::None);
	auto m_pad04 = new Pad(
		SCREEN_WIDTH + 600,
		SCREEN_HEIGHT / 2 + 200,
		43.f,
		89.f,
		PAD_TEXTURE_PATH
	);
	m_pad04->SetControlDevice(ControlDevice::None);

	m_ball->assignPadsCanCollideBall(m_leftPad, m_rightPad);

	m_player = new Player(
		SCREEN_WIDTH / 2 - 20,
		SCREEN_HEIGHT / 2 - 20,
		106.f,
		106.f,
		PLAYER_TEXTURE_PATH
	);
	Camera::getInstance()->setPosition(m_player->getPosition());
	m_listCanCollideWithPlayer = new std::map<int, GameObject*>();

	m_grid = new Grid();
	//m_grid->add(0, m_player);
	m_grid->add(1, m_ball);
	m_grid->add(2, m_leftPad);
	m_grid->add(3, m_rightPad);
	m_grid->add(4, m_pad03);
	m_grid->add(5, m_pad04);

	m_objectList = new std::map<int, GameObject*>();
	//m_objectList->insert(std::pair<int, GameObject*>(0, m_player));
	m_objectList->insert(std::pair<int, GameObject*>(1, m_ball));
	m_objectList->insert(std::pair<int, GameObject*>(2, m_leftPad));
	m_objectList->insert(std::pair<int, GameObject*>(3, m_rightPad));
	m_objectList->insert(std::pair<int, GameObject*>(4, m_pad03));
	m_objectList->insert(std::pair<int, GameObject*>(5, m_pad04));

}

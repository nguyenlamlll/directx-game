#include "stdafx.h"
#include "BossScene.h"


BossScene::BossScene()
{
	m_grid = new Grid();
	m_player = new Player(700, 900, 106.f, 106.f);

	Camera::getInstance();
	D3DXVECTOR2 position(700, 900);
	Camera::getInstance()->setPosition(position);

	m_listCanCollideWithPlayer = new std::map<int, GameObject*>();

	m_map = new GameMap(250, 250, 2500 / 250, 1500 / 250,
		L"Resources/map/JafarPlace/jafar-small-tileset.png",
		L"Resources/map/JafarPlace/jafar-small.csv");
	m_map->setMapPosition(D3DXVECTOR2(119, 121));

	this->loadPlayerConfigurationsFromFile();
	this->loadObjectsFromFileToGrid();
}


BossScene::~BossScene()
{
}

void BossScene::Update(float deltaTime)
{
	if (KeyboardInput::GetInstance()->isKeyTriggered(VK_F1))
	{
		this->loadPlayerConfigurationsFromFile();
		this->loadObjectsFromFileToGrid();
		return;
	}
	if (KeyboardInput::GetInstance()->isKeyTriggered(0x31))
	{
		SceneManager::getInstance()->changeScene(new PlayScene());
		return;
	}

	auto visibleObjects = m_grid->getVisibleObjects();
	for (auto it = visibleObjects->begin(); it != visibleObjects->end(); it++)
	{
		it->second->Update(deltaTime);
	}

	m_player->Update(deltaTime);
	auto playerPosition = m_grid->calculateObjectPositionOnGrid(m_player);
	m_listCanCollideWithPlayer->clear();
	m_grid->getCollidableObjects(m_listCanCollideWithPlayer, playerPosition.x, playerPosition.y);
	m_player->OnCollision(m_listCanCollideWithPlayer, deltaTime);
}

void BossScene::Draw()
{
	m_map->RenderMap();

	auto visibleObjects = m_grid->getVisibleObjects();
	for (auto it = visibleObjects->begin(); it != visibleObjects->end(); it++)
	{
		it->second->Draw();
	}

	m_player->Draw();
}

void BossScene::OnKeyDown(int keyCode)
{
}

void BossScene::OnKeyUp(int keyCode)
{
}

void BossScene::ReleaseAll()
{
	delete m_player;

	m_map->Release();
	delete m_map;

	m_listCanCollideWithPlayer->clear();
	delete m_listCanCollideWithPlayer;

	auto allObjects = m_grid->getAllObjects();
	for (auto it = allObjects->begin(); it != allObjects->end(); it++)
	{
		delete it->second;
	}
	m_grid->reset();
	delete m_grid;
}

void BossScene::loadPlayerConfigurationsFromFile()
{
	// Open file and read object positions, load them into the grid.
	std::ifstream file;
	std::string filename = "Resources/grid/JafarPlace/player.txt";
	file.open(filename);

	while (!file.eof())
	{
		std::string objectName;
		file >> objectName;

		// If file is empty, don't bother loading.
		if (objectName._Equal(""))
		{
			break;
		}

		// Ignore comments (strings begin with #)
		std::string line;
		if (objectName._Equal("#"))
		{
			std::getline(file, line);
			continue;
		}

		if (objectName._Equal("player"))
		{
			float x, y, w, h;
			file >> x;
			file >> y;
			file >> w;
			file >> h;
			m_player->setPosition(D3DXVECTOR2(x, y));
		}
		else if (objectName._Equal("camera"))
		{
			float x, y;
			file >> x;
			file >> y;
			Camera::getInstance()->setPosition(D3DXVECTOR2(x, y));
		}
	}
	file.close();
}

void BossScene::loadObjectsFromFileToGrid()
{
	// Reset the grid and clean up resources.
	auto allObjects = m_grid->getAllObjects();
	for (auto it = allObjects->begin(); it != allObjects->end(); it++)
	{
		delete it->second;
	}
	m_grid->reset();

	// Open file and read object positions, load them into the grid.
	std::ifstream file;
	std::string filename = "Resources/grid/JafarPlace/objects.txt";
	file.open(filename);

	int count = 0;
	while (!file.eof())
	{
		std::string objectName;
		file >> objectName;

		// If file is empty, don't bother loading.
		if (objectName._Equal(""))
		{
			break;
		}

		// Ignore comments (strings begin with #)
		std::string line;
		if (objectName._Equal("#"))
		{
			std::getline(file, line);
			continue;
		}

		count++;
		if (objectName._Equal("ground"))
		{
			//float x, y, w, h;
			//file >> x;
			//file >> y;
			//file >> w;
			//file >> h;
			//m_grid->add(new Ground(x, y, w, h));
		}
	}
	file.close();
}

#include "stdafx.h"
#include "BossScene.h"
#include "Player.h"

BossScene::BossScene()
{
	m_grid = new Grid();

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

	Sound::getInstance()->play("background-boss-level", true);

	m_blood = new BloodBar(75, 25, 0, 0);
	m_blood->attachPlayer(m_player);
	m_rubyScore = new RubyScores(280, 300, 0, 0);
	m_appleScore = new AppleScores(340, 300, 0, 0);
	m_lifeScore = new LifeScores(40, 300, 0, 0);
	m_aladdinScore = new AladdinScores(370, 25, 0, 0);
	m_aladdinScore->increaseScores(10);
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
		if (it->second->getTag() == Tag::BossTag)
		{
			it->second->OnCollision(m_player, deltaTime);
		}
	}

	auto playerPosition01 = m_grid->calculateObjectPositionOnGrid(m_player);
	m_listCanCollideWithPlayer->clear();
	m_grid->getCollidableObjects(m_listCanCollideWithPlayer, playerPosition01.x, playerPosition01.y);
	m_player->PreCollision(m_listCanCollideWithPlayer, deltaTime);

	m_player->Update(deltaTime);

	auto playerPosition = m_grid->calculateObjectPositionOnGrid(m_player);
	m_listCanCollideWithPlayer->clear();
	m_grid->getCollidableObjects(m_listCanCollideWithPlayer, playerPosition.x, playerPosition.y);
	m_player->OnCollision(m_listCanCollideWithPlayer, deltaTime);

	m_blood->Update(deltaTime);
	m_rubyScore->Update(deltaTime);
	m_lifeScore->Update(deltaTime);
	m_appleScore->Update(deltaTime);
	m_aladdinScore->Update(deltaTime);
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

	m_blood->Draw();
	m_rubyScore->Draw();
	m_lifeScore->Draw();
	m_appleScore->Draw();
	m_aladdinScore->Draw();
}

void BossScene::OnKeyDown(int keyCode)
{
}

void BossScene::OnKeyUp(int keyCode)
{
}

void BossScene::ReleaseAll()
{
	Sound::getInstance()->stop("background-boss-level");

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
			m_player = new Player(700, 900, w, h);
			m_player->setPosition(D3DXVECTOR2(x, y));
		}
		else if (objectName._Equal("camera"))
		{
			float x, y;
			file >> x;
			file >> y;
			Camera::getInstance()->setPosition(D3DXVECTOR2(x, y));
			Camera::getInstance()->attachPlayer(m_player);
			auto defaultBoundaries = Camera::getInstance()->getBoundaries();
			Camera::getInstance()->setBoundaries(945, 1531, defaultBoundaries.z, defaultBoundaries.w);
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
			float x, y, w, h, scaleWidth, scaleHeight;
			bool isDebug;
			file >> x;
			file >> y;
			file >> w;
			file >> h;
			file >> scaleWidth;
			file >> scaleHeight;
			file >> isDebug;
			Ground* ground = new Ground(x, y, w, h, scaleWidth, scaleHeight, isDebug);
			ground->setIsDebugVisible(isDebug);
			m_grid->add(count, ground);
		}
		else if (objectName._Equal("vertical-wall"))
		{
			string spriteName;
			float x, y, w, h, scaleWidth, scaleHeight;
			bool isDebug;
			file >> spriteName;
			file >> x;
			file >> y;
			file >> w;
			file >> h;
			file >> scaleWidth;
			file >> scaleHeight;
			file >> isDebug;
			VerticalWall* wall = new VerticalWall(spriteName, x, y, w, h, scaleWidth, scaleHeight, isDebug);
			wall->setIsDebugVisible(isDebug);
			m_grid->add(count, wall);
		}
		else if (objectName._Equal("boss"))
		{
			float x, y, w, h;
			bool isFacingRight;
			file >> x;
			file >> y;
			file >> w;
			file >> h;
			file >> isFacingRight;
			Boss* boss = new Boss(x, y, w, h, isFacingRight);
			boss->attachPlayer(m_player);
			m_grid->add(count, boss);
		}
	}
	file.close();
}

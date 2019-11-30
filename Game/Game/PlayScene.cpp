#include "stdafx.h"
#include "PlayScene.h"

#define SCREEN_WIDTH Global::GetInstance()->g_ScreenWidth
#define SCREEN_HEIGHT Global::GetInstance()->g_ScreenHeight

PlayScene::PlayScene()
{
	loadResources();

	m_map = new GameMap(500, 500, 3000 / 500, 2000 / 500, 
		L"Resources/map/dungeon-500-500-tileset.png", 
		L"Resources/map/dungeon-500-500.csv");
}


PlayScene::~PlayScene()
{
}

void PlayScene::Update(float deltaTime)
{
	if (KeyboardInput::GetInstance()->isKeyTriggered(VK_F1))
	{
		this->LoadGridFromFile();
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

void PlayScene::Draw()
{
	m_map->RenderMap();
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
	m_player = new Player(
		630,
		1580.5,
		106.f,
		106.f);
	Camera::getInstance();
	//D3DXVECTOR2 position(Global::GetInstance()->g_ScreenWidth / 2, (Global::GetInstance()->g_ScreenHeight / 2) - 0);
	D3DXVECTOR2 position(704.25, 1463.75);
	Camera::getInstance()->setPosition(position);
	m_listCanCollideWithPlayer = new std::map<int, GameObject*>();

	m_grid = new Grid();

	//this->SaveGridToFile();
	this->LoadGridFromFile();
}

void PlayScene::SaveGridToFile()
{
	std::ofstream file;
	std::string filename = "Resources/grid/playscene.txt";
	file.open(filename);
	auto allObjects = m_grid->getAllObjects();
	for (auto it = allObjects->begin(); it != allObjects->end(); it++)
	{
		switch (it->second->getTag())
		{
		case Tag::GroundTag:
		{
			file << "\nground ";
			file << it->second->getPosition().x 
				<< " " << it->second->getPosition().y
				<< " " << it->second->getWidth()
				<< " " << it->second->getHeight();
			break;
		}
		case Tag::PadTag:
		{
			file << "\npad ";
			file << it->second->getPosition().x
				<< " " << it->second->getPosition().y
				<< " " << it->second->getWidth()
				<< " " << it->second->getHeight();
			break;
		}
		case Tag::UnclassifiedTag:
		{
			file << "\nunclassified ";
			file << it->second->getPosition().x
				<< " " << it->second->getPosition().y
				<< " " << it->second->getWidth()
				<< " " << it->second->getHeight();
			break;
		}
		default:
		{
			break;
		}
		}
	}
}

void PlayScene::LoadGridFromFile()
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
	std::string filename = "Resources/grid/playscene.txt";
	file.open(filename);

	int count = 0;
	while (!file.eof())
	{
		std::string objectName;
		file >> objectName;
		if (objectName._Equal(""))
		{
			break;
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
		else if (objectName._Equal("thin-guard"))
		{
			float x, y, w, h;
			file >> x;
			file >> y;
			file >> w;
			file >> h;
			ThinGuard* thinGuard = new ThinGuard(x, y, w, h);
			thinGuard->attachPlayer(m_player);
			m_grid->add(count, thinGuard);
		}
		else if (objectName._Equal("mustache-guard"))
		{
			float x, y, w, h;
			file >> x;
			file >> y;
			file >> w;
			file >> h;
			MustacheGuard* mustacheGuard = new MustacheGuard(x, y, w, h);
			mustacheGuard->attachPlayer(m_player);
			m_grid->add(count, mustacheGuard);
		}
	}
	file.close();
}

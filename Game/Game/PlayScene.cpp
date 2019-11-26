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

	m_sprite = new Sprite(L"Resources/map/dungeon.png");
	//m_sprite->setCenter(D3DXVECTOR3(3200.f/2, 1600.f/2,0));
	//m_sprite->setFlipHorizontal(true);
	m_sprite->setPositionX(1000);
	m_sprite->setPositionY(-150);
	m_map = new GameMap(16, 16, 1504 / 16, 816 / 16, 
		L"Resources/Map2Level2-tileset.png", 
		L"Resources/Map2Level2.csv");
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
	m_map->RenderMap();
	m_sprite->Draw();
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
	//auto m_ball = new Ball(
	//	SCREEN_WIDTH / 2 + 50,
	//	SCREEN_HEIGHT / 2,
	//	22.f,
	//	22.f,
	//	BALL_TEXTURE_PATH);

	//m_ball->assignPadsCanCollideBall(m_leftPad, m_rightPad);

	m_player = new Player(
		150,
		280,
		106.f,
		106.f,
		PLAYER_TEXTURE_PATH
	);
	Camera::getInstance();
	D3DXVECTOR2 position(Global::GetInstance()->g_ScreenWidth / 2, (Global::GetInstance()->g_ScreenHeight / 2) - 250);
	Camera::getInstance()->setPosition(position);
	m_listCanCollideWithPlayer = new std::map<int, GameObject*>();

	m_grid = new Grid();
	//m_grid->add(9999, m_player);
	//m_grid->add(1, m_ball);
	//m_grid->add(2, m_leftPad);
	//m_grid->add(3, m_rightPad);
	//m_grid->add(4, m_pad03);
	//m_grid->add(5, m_pad04);

	m_objectList = new std::map<int, GameObject*>();
	//m_objectList->insert(std::pair<int, GameObject*>(0, m_player));
	//m_objectList->insert(std::pair<int, GameObject*>(1, m_ball));
	//m_objectList->insert(std::pair<int, GameObject*>(2, m_leftPad));
	//m_objectList->insert(std::pair<int, GameObject*>(3, m_rightPad));
	//m_objectList->insert(std::pair<int, GameObject*>(4, m_pad03));
	//m_objectList->insert(std::pair<int, GameObject*>(5, m_pad04));

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
			//int x, y, w, h;
			//file >> x;
			//file >> y;
			//file >> w;
			//file >> h;
			//m_grid->add(new Ground(x, y, w, h));
		}
		else if (objectName._Equal("pad"))
		{
			int x, y, w, h;
			file >> x;
			file >> y;
			file >> w;
			file >> h;
			m_grid->add(count, new Pad(x, y, w, h, PAD_TEXTURE_PATH));
		}
		else if (objectName._Equal("thin-guard"))
		{
			int x, y, w, h;
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
			int x, y, w, h;
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

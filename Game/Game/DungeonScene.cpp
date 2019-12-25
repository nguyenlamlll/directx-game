#include "stdafx.h"
#include "DungeonScene.h"

#define SCREEN_WIDTH Global::GetInstance()->g_ScreenWidth
#define SCREEN_HEIGHT Global::GetInstance()->g_ScreenHeight

DungeonScene::DungeonScene()
{
	loadResources();

	m_map = new GameMap(500, 500, 3000 / 500, 2000 / 500,
		L"Resources/map/dungeon-500-500-tileset.png",
		L"Resources/map/dungeon-500-500.csv");
}

void DungeonScene::initialize()
{
	Sound::getInstance()->play("background-level-1", true);
}

DungeonScene::~DungeonScene()
{
}

void DungeonScene::Update(float deltaTime)
{
	if (KeyboardInput::GetInstance()->isKeyTriggered(VK_F3))
	{
		m_player->setPosition(D3DXVECTOR2(630, 1580.5));
		Camera::getInstance()->setPosition(D3DXVECTOR2(m_player->getPosition().x + 74, 1463.75));
		Camera::getInstance()->setBoundaries(700, 2550, 650, 1463.75);
		m_player->changeState(PlayerStates::Standing);
		return;
	}
	if (KeyboardInput::GetInstance()->isKeyTriggered(VK_F1))
	{
		this->LoadGridFromFile();
		this->loadWallsFromFileToGrid();
		return;
	}
	if (KeyboardInput::GetInstance()->isKeyTriggered(0x32))
	{
		SceneManager::getInstance()->changeScene(new LevelCompleteScene(new BossScene()));
		return;
	}

	auto visibleObjects = m_grid->getVisibleObjects();
	for (auto it = visibleObjects->begin(); it != visibleObjects->end(); it++)
	{
		it->second->Update(deltaTime);
		if (it->second->getTag() == Tag::MustaheGuardTag || 
			it->second->getTag() == Tag::ThinGuardTag ||
			it->second->getTag() == Tag::SkeletonTag ||
			it->second->getTag() == Tag::BatTag
			)
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

	// Exceptionally, check if player hits exit door.
	if (m_listCanCollideWithPlayer->count(1) == 1)
	{
		if (Collision::getInstance()->isColliding(m_player->GetBoundingBox(), m_listCanCollideWithPlayer->at(1)->GetBoundingBox()))
		{
			SceneManager::getInstance()->changeScene(new LevelCompleteScene(new BossScene()));
			return;
		}
	}


	// Check and delete death objects
	//auto objects = m_grid->getVisibleObjects();
	//for (auto it = objects->begin(); it != objects->end();)
	//{
	//	auto health = dynamic_cast<Health*>(it->second);
	//	if (health != nullptr && health->getCurrentHealth() <= 0.0f)
	//	{
	//		m_grid->remove(it->first, it->second);
	//		//delete it->second;
	//		it = objects->erase(it);
	//	}
	//	else
	//	{
	//		it++;
	//	}
	//}

	visibleObjects->clear();
	visibleObjects = m_foregroundGrid->getVisibleObjects();
	for (auto it = visibleObjects->begin(); it != visibleObjects->end(); it++)
	{
		it->second->Update(deltaTime);
	}

	m_blood->Update(deltaTime);
	m_rubyScore->Update(deltaTime);
	m_lifeScore->Update(deltaTime);
	m_appleScore->Update(deltaTime);
	m_aladdinScore->Update(deltaTime);
}

void DungeonScene::Draw()
{
	m_map->RenderMap();

	auto visibleObjects = m_grid->getVisibleObjects();
	for (auto it = visibleObjects->begin(); it != visibleObjects->end(); it++)
	{
		it->second->Draw();
	}
	m_player->Draw();

	m_firstColumn->Draw();
	m_secondColumn->Draw();
	m_thirdColumn->Draw();
	m_fourthColumn->Draw();

	auto visibleObjects2 = m_foregroundGrid->getVisibleObjects();
	for (auto it = visibleObjects2->begin(); it != visibleObjects2->end(); it++)
	{
		it->second->Draw();
	}
	m_blood->Draw();
	m_rubyScore->Draw();
	m_lifeScore->Draw();
	m_appleScore->Draw();
	m_aladdinScore->Draw();
}

void DungeonScene::OnKeyDown(int keyCode)
{
}

void DungeonScene::OnKeyUp(int keyCode)
{
}

void DungeonScene::ReleaseAll()
{
	Sound::getInstance()->stop("background-level-1");

	delete m_player;
	delete m_blood;
	delete m_rubyScore;

	m_map->Release();
	delete m_map;

	delete m_firstColumn;
	delete m_secondColumn;
	delete m_thirdColumn;
	delete m_fourthColumn;

	m_listCanCollideWithPlayer->clear();
	delete m_listCanCollideWithPlayer;

	auto allObjects = m_grid->getAllObjects();
	for (auto it = allObjects->begin(); it != allObjects->end(); it++)
	{
		std::wstring raw = L"Item index deleting: " + std::to_wstring(it->first);
		LPCWSTR outputString = raw.c_str();
		OutputDebugString(outputString);
		OutputDebugString(L"\n");
		delete it->second;
	}
	m_grid->reset();
	delete m_grid;

	allObjects->clear();
	allObjects = m_foregroundGrid->getAllObjects();
	for (auto it = allObjects->begin(); it != allObjects->end(); it++)
	{
		delete it->second;
	}
	m_foregroundGrid->reset();
	delete m_foregroundGrid;
}

void DungeonScene::loadResources()
{
	m_player = new Player(
		630,
		1580.5,
		36.0f,
		50.f);
	//m_player->setPosition(D3DXVECTOR2(2200.f, 1580.5f));

	m_blood = new BloodBar(75, 25, 0, 0);
	m_blood->attachPlayer(m_player);
	m_rubyScore = new RubyScores(280, 300, 0, 0);
	m_appleScore = new AppleScores(340, 300, 0, 0);
	m_lifeScore = new LifeScores(40, 300, 0, 0);
	m_aladdinScore = new AladdinScores(370, 25, 0, 0);
	m_aladdinScore->increaseScores(10);

	Camera::getInstance();
	Camera::getInstance()->attachPlayer(m_player);
	//D3DXVECTOR2 position(Global::GetInstance()->g_ScreenWidth / 2, (Global::GetInstance()->g_ScreenHeight / 2) - 0);
	D3DXVECTOR2 position(704.25, 1463.75);
	Camera::getInstance()->setPosition(D3DXVECTOR2(m_player->getPosition().x + 74, 1463.75));
	Camera::getInstance()->setBoundaries(700, 2550, 650, 1463.75);

	m_listCanCollideWithPlayer = new std::map<int, GameObject*>();

	m_grid = new Grid();
	m_foregroundGrid = new Grid();

	//this->SaveGridToFile();
	this->LoadGridFromFile();
	this->loadWallsFromFileToGrid();

}

void DungeonScene::SaveGridToFile()
{
	std::ofstream file;
	std::string filename = "Resources/grid/DungeonScene.txt";
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

void DungeonScene::LoadGridFromFile()
{
	// Reset the grid and clean up resources.
	auto allObjects = m_grid->getAllObjects();
	for (auto it = allObjects->begin(); it != allObjects->end(); it++)
	{
		delete it->second;
	}
	m_grid->reset();

	allObjects->clear();
	allObjects = m_foregroundGrid->getAllObjects();
	for (auto it = allObjects->begin(); it != allObjects->end(); it++)
	{
		delete it->second;
	}
	m_foregroundGrid->reset();

	// Open file and read object positions, load them into the grid.
	std::ifstream file;
	std::string filename = "Resources/grid/playscene.txt";
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
		else if (objectName._Equal("apple-item"))
		{
			float x, y, w, h;
			file >> x;
			file >> y;
			file >> w;
			file >> h;
			AppleItem* appleItem = new AppleItem(x, y, w, h);
			appleItem->attachPlayer(m_player);
			m_grid->add(count, appleItem);
		}
		else if (objectName._Equal("blue-heart-item"))
		{
			float x, y, w, h;
			file >> x;
			file >> y;
			file >> w;
			file >> h;
			BlueHeartItem* blueHeartItem = new BlueHeartItem(x, y, w, h);
			blueHeartItem->attachPlayer(m_player);
			m_grid->add(count, blueHeartItem);
		}
		else if (objectName._Equal("genie-face-item"))
		{
			float x, y, w, h;
			file >> x;
			file >> y;
			file >> w;
			file >> h;
			GenieFaceItem* genieFaceItem = new GenieFaceItem(x, y, w, h);
			genieFaceItem->attachPlayer(m_player);
			m_grid->add(count, genieFaceItem);
		}
		else if (objectName._Equal("genie-jar-item"))
		{
			float x, y, w, h;
			file >> x;
			file >> y;
			file >> w;
			file >> h;
			GenieJarItem* genieJarItem = new GenieJarItem(x, y, w, h);
			genieJarItem->attachPlayer(m_player);
			m_grid->add(count, genieJarItem);
		}
		else if (objectName._Equal("ruby-item"))
		{
			float x, y, w, h;
			int indexFrame;
			file >> x;
			file >> y;
			file >> w;
			file >> h;
			file >> indexFrame;
			RubyItem* rubyItem = new RubyItem(x, y, w, h, indexFrame);
			rubyItem->attachPlayer(m_player);
			m_grid->add(count, rubyItem);
		}
		else if (objectName._Equal("peddler"))
		{
			float x, y, w, h;
			file >> x;
			file >> y;
			file >> w;
			file >> h;
			Peddler* peddler = new Peddler(x, y, w, h);
			peddler->attachPlayer(m_player);
			m_grid->add(count, peddler);
		}
		else if (objectName._Equal("floating-brick"))
		{
			float x, y, w, h;
			int type;
			file >> x;
			file >> y;
			file >> w;
			file >> h;
			file >> type;
			FloatingBrick* floatingbrick = new FloatingBrick(x, y, w, h, type);
			m_grid->add(count, floatingbrick);
		}
		else if (objectName._Equal("bat-enemy"))
		{
			float x, y, w, h;
			float lm_left, lm_right;
			file >> x;
			file >> y;
			file >> w;
			file >> h;
			file >> lm_left;
			file >> lm_right;
			Bat* batObject = new Bat(x, y, w, h, lm_left, lm_right);
			batObject->attachPlayer(m_player);
			m_grid->add(count, batObject);
		}
		else if (objectName._Equal("skeleton-guard"))
		{
			float x, y, w, h;
			bool isFacingRight;
			file >> x;
			file >> y;
			file >> w;
			file >> h;
			file >> isFacingRight;
			Skeleton* skeleton = new Skeleton(x, y, w, h, isFacingRight);
			skeleton->attachPlayer(m_player);
			m_grid->add(count, skeleton);
		}
		else if (objectName._Equal("hanging-morning-star"))
		{
			float x, y, w, h;
			int indexFrame;
			file >> x;
			file >> y;
			file >> w;
			file >> h;
			file >> indexFrame;
			HangingMorningStar* hangingmorningstar = new HangingMorningStar(x, y, w, h, indexFrame);
			m_grid->add(count, hangingmorningstar);
		}
		else if (objectName._Equal("spike-spike"))
		{
			float x, y, w, h;
			int type;
			file >> x;
			file >> y;
			file >> w;
			file >> h;
			file >> type;
			Spike* spike = new Spike(x, y, w, h, type);
			m_grid->add(count, spike);
		}
		else if (objectName._Equal("exit-door"))
		{
			float x, y, w, h;
			file >> x;
			file >> y;
			file >> w;
			file >> h;
			ExitDoor* exitDoor = new ExitDoor(x, y, w, h);
			m_grid->add(count, exitDoor);
		}
		else if (objectName._Equal("first-column"))
		{
			float x, y, w, h;
			file >> x;
			file >> y;
			file >> w;
			file >> h;
			m_firstColumn = new Sprite(L"Resources/map/first-column.png", D3DCOLOR_XRGB(255, 255, 255));
			m_firstColumn->setPositionX(x);
			m_firstColumn->setPositionY(y);
		}
		else if (objectName._Equal("second-column"))
		{
			float x, y, w, h;
			file >> x;
			file >> y;
			file >> w;
			file >> h;
			m_secondColumn = new Sprite(L"Resources/map/second-column.png", D3DCOLOR_XRGB(255, 255, 255));
			m_secondColumn->setPositionX(x);
			m_secondColumn->setPositionY(y);
		}
		else if (objectName._Equal("third-column"))
		{
			float x, y, w, h;
			file >> x;
			file >> y;
			file >> w;
			file >> h;
			m_thirdColumn = new Sprite(L"Resources/map/third-column.png", D3DCOLOR_XRGB(255, 255, 255));
			m_thirdColumn->setPositionX(x);
			m_thirdColumn->setPositionY(y);
		}
		else if (objectName._Equal("fourth-column"))
		{
			float x, y, w, h;
			file >> x;
			file >> y;
			file >> w;
			file >> h;
			m_fourthColumn = new Sprite(L"Resources/map/fourth-column.png", D3DCOLOR_XRGB(255, 255, 255));
			m_fourthColumn->setPositionX(x);
			m_fourthColumn->setPositionY(y);
		}
		else if (objectName._Equal("chains-ui"))
		{
			float x, y, w, h;
			float scaleX, scaleY;
			file >> x;
			file >> y;
			file >> w;
			file >> h;
			file >> scaleX;
			file >> scaleY;
			ForegroundChains* foregroundChains = new ForegroundChains(x, y, w, h, scaleX, scaleY);
			m_foregroundGrid->add(count, foregroundChains);
		}
	}
	file.close();
}

void DungeonScene::loadWallsFromFileToGrid()
{
	// Open file and read object positions, load them into the grid.
	std::ifstream file;
	std::string filename = "Resources/grid/walls.txt";
	file.open(filename);

	int count = m_grid->getAllObjects()->size() + 1;
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
			std::string spriteName;
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
		else if (objectName._Equal("climb-area"))
		{
			float x, y, w, h;
			bool isDebug;
			file >> x;
			file >> y;
			file >> w;
			file >> h;
			file >> isDebug;
			ClimbArea* climbArea = new ClimbArea(x, y, w, h, isDebug);
			m_grid->add(count, climbArea);
		}
	}
	file.close();
}

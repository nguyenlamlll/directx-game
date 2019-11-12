#include "stdafx.h"
#include "GameMap.h"

std::vector<int> GameMap::getMapDataFromFile(LPCWSTR dataFilePath)
{
	std::ifstream file(dataFilePath);
	std::vector<int> data = std::vector<int>();
	if (file.good())
	{
		std::string curData = "";

		int i = 0;
		while (file >> curData)
		{
			i++;
			int x = atoi(curData.c_str());
			data.push_back(x);
		}
		file.close();
	}
	return data;
}

GameMap::GameMap(
	int tileWidth,
	int tileHeight,
	int numTilesWidth,
	int numTileHeight,
	LPCWSTR tileSetPath,
	LPCWSTR dataFilePath)
{
	m_data = getMapDataFromFile(dataFilePath);
	/*if (data.size() != numTilesWidth * numTileHeight)
	{
		MessageBox(NULL, "Error on retriving map data", "Error", MB_OK);
		PostQuitMessage(0);
		return;
	}*/
	if (m_data.empty())
	{
		MessageBox(NULL, L"Error on retriving map data", L"Error", MB_OK);
		return;
	}
	this->m_tileWidth = tileWidth;
	this->m_tileHeight = tileHeight;
	this->m_numTilesHeight = numTileHeight;
	this->m_numTilesWidth = numTilesWidth;

	m_tileset = new Tileset(tileSetPath, tileWidth, tileHeight);
	//m_tileset2 = new Tileset(L"Resources/map/dungeon_tileset_02.png", tileWidth, tileHeight);

	//Initialize game world map width and height
	GLOBAL->g_WorldMapWidth = numTilesWidth * tileWidth;
	GLOBAL->g_WorldMapHeight = numTileHeight * tileHeight;
}

GameMap::~GameMap()
{
}

void GameMap::RenderMap()
{
	// Calculate offset
	int offX = floor(Camera::getInstance()->getBound().left / m_tileWidth);
	int offY = floor(Camera::getInstance()->getBound().top / m_tileHeight); // Reverted because the y axis is reverted.

	// Caculate number of columns and rows that will be drawn
	int columnsDraw = ceil(Camera::getInstance()->getWidth() / m_tileWidth);
	int rowsDraw = ceil(Camera::getInstance()->getHeight() / m_tileHeight);
	int count = 0;
	for (int y = 0; y <= rowsDraw; y++)
	{
		for (int x = 0; x <= columnsDraw; x++)
		{
			// If not check, the map will loop.
			if ((x + offX) * m_tileWidth < 0 || (x + offX) * m_tileWidth > GLOBAL->g_WorldMapWidth) continue;

			int pos = (offY + y) * m_numTilesWidth + (offX + x);
			if (pos < 0 || pos >= m_data.size())
			{
				return;
			}
			int tileID = m_data.at(pos);
			if (tileID < 0)
			{
				return;
			}
			if (tileID == 16) {
				int kk = 0;
			}

			m_tileset->DrawTile(
				tileID,
				D3DXVECTOR3((x + offX) * m_tileWidth, (y + offY) * m_tileHeight, 0),
				D3DXVECTOR3(Camera::getInstance()->getPosition().x, Camera::getInstance()->getPosition().y, 0)
			);

			//if (++count >= 500) return;
		}
	}

	//MapCell** mapCell = this->info->getMap();

	//RECT viewport = Camera::getInstance()->getBound();
	//int columnBegin = (int)(viewport.left / m_tileWidth + 0.5f) - 1;
	//int columnEnd = columnBegin + Camera::getInstance()->getWidth() / m_tileWidth + 2;
	//int rowBegin = (int)((Global::GetInstance()->g_WorldMapHeight - viewport.top) / m_tileHeight);
	//int rowEnd = rowBegin + Camera::getInstance()->getHeight() / m_tileHeight + 1;

	//for (int col = columnBegin; col < columnEnd; col++)
	//{
	//	for (int row = rowBegin; row < rowEnd; row++)
	//	{
	//		if (row <= -1 || col <= -1)
	//		{
	//			continue;
	//		}
	//		m_tileset->DrawTile(
	//			tileID,
	//			D3DXVECTOR3((x + offX) * m_tileWidth, (y + offY) * m_tileHeight, 0),
	//			D3DXVECTOR3(Camera::getInstance()->getPosition().x, Camera::getInstance()->getPosition().y, 0)
	//		);

	//		//spriteData.rotate = 0;
	//		//spriteData.texture = this->texture->getTexture();
	//		//spriteData.position.x = (float)col*tileW;
	//		//spriteData.position.y = MAP_HEIGHT - (float)row*tileH;
	//		//spriteData.scale = VECTOR2(1.0f, 1.0f);
	//		//spriteData.origin = VECTOR2(0, 0);
	//		//spriteData.rect = *(mapCell[row][col].rect);
	//		//spriteData.width = tileW;
	//		//spriteData.height = tileH;
	//		//spriteData.flipVertical = false;
	//		//spriteData.flipHorizontal = false;

	//		//graphics->drawSprite(spriteData);
	//	}
	//}
}

void GameMap::Release()
{
	if (m_tileset != nullptr)
	{
		delete m_tileset;
	}
	m_data.clear();
}

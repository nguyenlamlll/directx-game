#pragma once
#include "Tileset.h"
#include "Camera.h"
#include <vector>

struct MapCell
{
	// rect of cell
	RECT* rect;
	//visible: true map cell will draw or not 
	bool visible;
};

class GameMap
{
private:
	D3DXVECTOR2 m_mapPosition;

	//list of rectangle use for mapCell
	std::vector<RECT*> *listRectOfMapCell;
	//two dimension array : represent map
	MapCell** map;


	std::vector<int> m_data;
	std::vector<int> m_data2;
	Tileset* m_tileset;
	Tileset* m_tileset2;
	int m_tileWidth;
	int m_tileHeight;
	int	m_numTilesWidth;
	int m_numTilesHeight;

	std::vector<int> getMapDataFromFile(LPCWSTR dataFilePath);
public:
	GameMap(int tileWidth, int tileHeight, int numTilesWidth, int numTileHeight, LPCWSTR tileSetPath, LPCWSTR dataFilePath);
	~GameMap();

	void RenderMap();

	void Release();

};


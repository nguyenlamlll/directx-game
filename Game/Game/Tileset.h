#pragma once
#include "Sprite.h"
#include "Tile.h"

#include <iostream>
#include <fstream>

class Tileset
{
private:
	Sprite* m_tileset;
	Tile* m_tile;
	int	m_numTilesWidth;
	int m_numTilesHeight;
	int	m_tileWidth;
	int m_tileHeight;
public:
	Tileset(LPCWSTR mapFilePath, int tileWidth, int tileHeight);
	~Tileset();

	void DrawTile(int tileId, D3DXVECTOR3 posToDraw, D3DXVECTOR3 cameraPos);
};


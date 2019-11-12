#include "stdafx.h"
#include "Tileset.h"

Tileset::Tileset(LPCWSTR mapFilePath, int tileWidth, int tileHeight)
{
	m_tileset = new Sprite(mapFilePath);
	m_numTilesWidth = m_tileset->getTextureWidth() / tileWidth;
	m_numTilesHeight = m_tileset->getTextureHeight() / tileHeight;
	this->m_tileWidth = tileWidth;
	this->m_tileHeight = tileHeight;

	//reset tileset to size of each tile
	m_tileset->setTextureWidth(tileWidth);
	m_tileset->setTextureWidth(tileHeight);
}

Tileset::~Tileset()
{
	if (m_tileset != nullptr)
	{
		delete m_tileset;
	}
}

void Tileset::DrawTile(int tileId, D3DXVECTOR3 posToDraw, D3DXVECTOR3 cameraPos)
{
	m_tile = new Tile(
		(tileId % m_numTilesWidth) * m_tileWidth, 
		(tileId / m_numTilesWidth) * m_tileWidth, 
		m_tileWidth, 
		m_tileHeight);
	if (m_tile == nullptr)
	{
		return;
	}

	//m_tileset->Draw(posToDraw, cameraPos, m_tile->getSourceRect(), D3DXVECTOR3(0, 0, 0));
	m_tileset->setPositionX(posToDraw.x);
	m_tileset->setPositionY(posToDraw.y);
	m_tileset->setSourceRect(m_tile->getSourceRect());
	m_tileset->setCenter(D3DXVECTOR3(0,0,0));
	m_tileset->Draw();

	delete m_tile;
}

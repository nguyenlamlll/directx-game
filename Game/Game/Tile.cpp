#include "stdafx.h"
#include "Tile.h"

Tile::Tile(int x, int y, int width, int height)
{
	this->m_positionX = x;
	this->m_positionY = y;
	this->m_tileWidth = width;
	this->m_tileHeight = height;
}

Tile::~Tile()
{
}

RECT Tile::getSourceRect()
{
	RECT r;
	r.left = m_positionX;
	r.top = m_positionY;
	r.right = r.left + m_tileWidth;
	r.bottom = r.top + m_tileHeight;

	return r;
}

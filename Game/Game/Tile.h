#pragma once
class Tile
{
private:
	int m_positionX;
	int m_positionY;
	int m_tileWidth;
	int m_tileHeight;
public:
	/**
		Initilaize the Tile
		x:		the left of this tile, compare to world map
		y:		the top of this tile, compare to wolrd map
		width:	the width of this tile
		hieght:the height of this tile
	**/
	Tile(int x, int y, int width, int height);
	~Tile();

	//Get the rectangle of a tile
	RECT getSourceRect();
};


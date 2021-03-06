#include "stdafx.h"
#include "Grid.h"


Grid::Grid()
{
	// Clear the grid.
	for (int x = 0; x < NUM_COLUMNS; x++)
	{
		for (int y = 0; y < NUM_ROWS; y++)
		{
			cells[x][y] = new Cell();
		}
	}
}


Grid::~Grid()
{
	for (int x = 0; x < NUM_COLUMNS; x++)
	{
		for (int y = 0; y < NUM_ROWS; y++)
		{
			delete cells[x][y];
			cells[x][y] = nullptr;
		}
	}
}

void Grid::reset()
{
	for (int x = 0; x < NUM_COLUMNS; x++)
	{
		for (int y = 0; y < NUM_ROWS; y++)
		{
			delete cells[x][y];
			cells[x][y] = new Cell();
		}
	}
}

void Grid::CheckAndAddOversizedObject(GameObject * object, D3DXVECTOR2 &objectPositionOnGrid, int id)
{
	auto width = object->GetBoundingBox().width;
	auto height = object->GetBoundingBox().height;
	auto bottomRightPositionOnGrid = calculateObjectPositionOnGrid(
		object->getPosition().x + width,
		object->getPosition().y - height // TODO: Check with the map to see if this axis is correct
	);
	if ((objectPositionOnGrid.x != bottomRightPositionOnGrid.x) || (objectPositionOnGrid.y != bottomRightPositionOnGrid.y))
	{
		for (int i = objectPositionOnGrid.x; i <= bottomRightPositionOnGrid.x; i++)
		{
			for (int j = objectPositionOnGrid.y; j >= bottomRightPositionOnGrid.y; j--) // From top-left go down to bottom right.
			{
				// Does not need to check cell [objectPositionOnGrid.x][objectPositionOnGrid.y].
				// Because std::map only allows unique pairs.
				// So added object in operation above will not be re-added in this loop.
				cells[i][j]->add(id, object);
			}
		}
	}
}

void Grid::CheckAndAddOversizedObject(GameObject * object, int x, int y, D3DXVECTOR2 & objectPositionOnGrid, int id)
{
	auto width = object->GetBoundingBox().width;
	auto height = object->GetBoundingBox().height;
	auto bottomRightPositionOnGrid = calculateObjectPositionOnGrid(
		x + width,
		y - height // TODO: Check with the map to see if this axis is correct
	);
	if ((objectPositionOnGrid.x != bottomRightPositionOnGrid.x) || (objectPositionOnGrid.y != bottomRightPositionOnGrid.y))
	{
		for (int i = objectPositionOnGrid.x; i <= bottomRightPositionOnGrid.x; i++)
		{
			for (int j = objectPositionOnGrid.y; j >= bottomRightPositionOnGrid.y; j--) // From top-left go down to bottom right.
			{
				// Does not need to check cell [objectPositionOnGrid.x][objectPositionOnGrid.y].
				// Because std::map only allows unique pairs.
				// So added object in operation above will not be re-added in this loop.
				cells[i][j]->add(id, object);
			}
		}
	}
}

void Grid::add(int id, GameObject * object)
{
	auto objectPositionOnGrid = calculateObjectPositionOnGrid(object);

	cells[(int)objectPositionOnGrid.x][(int)objectPositionOnGrid.y]->add(id, object);

	// If an object is bigger than a cell, add that object to all cells which it resides.
	CheckAndAddOversizedObject(object, objectPositionOnGrid, id);
}

void Grid::add(int id, GameObject * object, int x, int y)
{
	auto objectPositionOnGrid = calculateObjectPositionOnGrid(x, y);

	cells[(int)objectPositionOnGrid.x][(int)objectPositionOnGrid.y]->add(id, object);

	// If an object is bigger than a cell, add that object to all cells which it resides.
	CheckAndAddOversizedObject(object, x, y, objectPositionOnGrid, id);
}

D3DXVECTOR2 Grid::calculateObjectPositionOnGrid(GameObject * object)
{
	int cellX = (int)(object->getPosition().x / Grid::CELL_SIZE);
	int cellY = (int)(object->getPosition().y / Grid::CELL_SIZE);
	return D3DXVECTOR2(cellX, cellY);
}

// Calculate which cell on the grid that the given position lies inside.
// We can use this function to calculate objects that are not initalized (yet) or do not have sprites to use sprite->getPosition().
D3DXVECTOR2 Grid::calculateObjectPositionOnGrid(int x, int y)
{
	int cellX = (int)(x / Grid::CELL_SIZE);
	int cellY = (int)(y / Grid::CELL_SIZE);
	return D3DXVECTOR2(cellX, cellY);
}

std::map<int, GameObject*>* Grid::getAllObjects()
{
	auto result = new std::map<int, GameObject*>();
	for (int x = 0; x < NUM_COLUMNS; x++)
	{
		for (int y = 0; y < NUM_ROWS; y++)
		{
			auto objects = cells[x][y]->getAllObjects();
			result->insert(objects->begin(), objects->end());
		}
	}
	return result;
}

void Grid::getCollidableObjects(std::map<int, GameObject*>* result, int column, int row)
{
	// References: https://gameprogrammingpatterns.com/spatial-partition.html?fbclid=IwAR3KCo4gASEb1z0P3pgGv_Ttb7nQP_-58MCYzyvOlo6_ft3IjEuTXuozZWQ
	if (column >= NUM_COLUMNS) return;
	if (row >= NUM_ROWS) return;

	auto objects = cells[column][row]->getAllObjects();
	result->insert(objects->begin(), objects->end());

	if (column > 0 && row > 0)
	{
		objects = cells[column - 1][row - 1]->getAllObjects();
		result->insert(objects->begin(), objects->end());
	}
	if (column > 0)
	{
		objects = cells[column - 1][row]->getAllObjects();
		result->insert(objects->begin(), objects->end());

		if (column < NUM_COLUMNS - 1)
		{
			objects = cells[column + 1][row]->getAllObjects();
			result->insert(objects->begin(), objects->end());
		}

		if (row < NUM_ROWS - 1)
		{
			objects = cells[column - 1][row + 1]->getAllObjects();
			result->insert(objects->begin(), objects->end());
		}
	}
	if (row > 0)
	{
		objects = cells[column][row - 1]->getAllObjects();
		result->insert(objects->begin(), objects->end());

		if (row < NUM_ROWS - 1)
		{
			objects = cells[column][row + 1]->getAllObjects();
			result->insert(objects->begin(), objects->end());
		}

		if (column < NUM_COLUMNS - 1)
		{
			objects = cells[column + 1][row - 1]->getAllObjects();
			result->insert(objects->begin(), objects->end());
		}
	}

	if (column < NUM_COLUMNS - 1 && row < NUM_ROWS - 1)
	{
		objects = cells[column + 1][row + 1]->getAllObjects();
		result->insert(objects->begin(), objects->end());
	}
}

std::map<int, GameObject*>* Grid::getVisibleObjects()
{
	std::map<int, GameObject*>* visibleObjects = new std::map<int, GameObject*>();

	std::vector<Cell*> visibleCells;
	int cellX = (int)((Camera::getInstance()->getPosition().x - Global::GetInstance()->g_ScreenWidth / 2) / Grid::CELL_SIZE);
	int cellY = (int)((Camera::getInstance()->getPosition().y - Global::GetInstance()->g_ScreenHeight / 2) / Grid::CELL_SIZE);
	D3DXVECTOR2 objectPositionOnGrid(cellX, cellY);
	auto width = Camera::getInstance()->getWidth();
	auto height = Camera::getInstance()->getHeight();
	auto bottomRightPositionOnGrid = calculateObjectPositionOnGrid(
		Camera::getInstance()->getPosition().x + width,
		Camera::getInstance()->getPosition().y + height // TODO: Check with the map to see if this axis is correct
	);
	if ((objectPositionOnGrid.x != bottomRightPositionOnGrid.x) || (objectPositionOnGrid.y != bottomRightPositionOnGrid.y))
	{
		for (int i = objectPositionOnGrid.x; i <= bottomRightPositionOnGrid.x; i++)
		{
			if (i < 0 || i >= NUM_COLUMNS) continue;
			for (int j = objectPositionOnGrid.y; j <= bottomRightPositionOnGrid.y; j++) // From top-left go down to bottom right.
			{
				if (j < 0 || j >= NUM_ROWS ) continue;
				visibleCells.push_back(cells[i][j]);
			}
		}
	}

	for (auto cell : visibleCells)
	{
		auto objects = cell->getAllObjects();
		for (auto it = objects->begin(); it != objects->end(); it++)
		{
			visibleObjects->insert(std::pair<int, GameObject*>(it->first, it->second));
		}
	}
	return visibleObjects;
}

void Grid::remove(int id, GameObject* object)
{
	auto position = calculateObjectPositionOnGrid(object);
	cells[(int)position.x][(int)position.y]->remove(id);
}

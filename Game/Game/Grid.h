#pragma once
#include "Cell.h"
#include "GameObject.h"
#include "Global.h"
#include "Camera.h"

#include <map>
#include <vector>

class Grid
{
public:
	// Create a grid for a prefixed map.
	Grid();
	~Grid();

	// Edge size of a cell
	static const int CELL_SIZE = 400;

	// Total number of columns based on prefixed map width
	static const int NUM_COLUMNS = MAP_WIDTH / CELL_SIZE;

	// Total number of rows based on prefixed map height
	static const int NUM_ROWS = MAP_HEIGHT / CELL_SIZE;

	void CheckAndAddOversizedObject(GameObject * object, D3DXVECTOR2 &objectPositionOnGrid, int id);
	void CheckAndAddOversizedObject(GameObject * object, int x, int y, D3DXVECTOR2 &objectPositionOnGrid, int id);
	void add(int id, GameObject* object);
	void add(int id, GameObject* object, int x, int y);
	D3DXVECTOR2 calculateObjectPositionOnGrid(GameObject* object);
	D3DXVECTOR2 calculateObjectPositionOnGrid(int x, int y);

	std::map<int, GameObject*>* getAllObjects(int column, int row) { return cells[column][row]->getAllObjects(); }
	std::map<int, GameObject*>* getAllObjects();

	// Return a list of colliable objects of an object sitting in one cell. 
	// We scan 4 others adjacent cells as well.
	// Pass a cell position to the function to retrieve collidable objects in that cell and 4 adjacent cells.
	void getCollidableObjects(std::map<int, GameObject*>* result, int column, int row);

	// Get objects from cells that collide with the camera viewport.
	// Objects outside camera view is obviously not seen, hence they are not visible.
	// Only visible objects should be drawn to save computer resource.
	std::map<int, GameObject*>* getVisibleObjects();

private:
	Cell* cells[NUM_COLUMNS][NUM_ROWS] = {};
};


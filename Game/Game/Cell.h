#pragma once
#include <map>
#include <vector>
#include "GameObject.h"
class Cell
{
private: 
	std::map<int, GameObject*>* listOfObjects = nullptr;
public:
	Cell();
	~Cell();

	void add(int id, GameObject* object);
	std::map<int, GameObject*>* getAllObjects();
};


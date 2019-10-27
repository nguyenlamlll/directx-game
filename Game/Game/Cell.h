#pragma once
#include <map>
#include "GameObject.h"
class Cell
{
private: 
	std::map<int, GameObject*>* listOfObjects;
public:
	Cell();
	~Cell();

	void add(int id, GameObject* object);
	std::map<int, GameObject*>* getAllObjects() { return listOfObjects; }
};


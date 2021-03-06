#include "stdafx.h"
#include "Cell.h"


Cell::Cell()
{
	listOfObjects = new std::map<int, GameObject*>();
}


Cell::~Cell()
{
	//for (auto it = listOfObjects->begin(); it != listOfObjects->end(); it++)
	//{
	//	delete it->second;
	//	it->second = nullptr;
	//}
	listOfObjects->clear();
	delete listOfObjects;
}

void Cell::add(int id, GameObject * object)
{
	listOfObjects->insert(std::pair<int, GameObject*>(id, object));
}

void Cell::remove(int id)
{
	auto it = listOfObjects->find(id);
	listOfObjects->erase(it);
}

std::map<int, GameObject*>* Cell::getAllObjects()
{
	if (listOfObjects) {
		return listOfObjects;
	}
	else {
		return NULL;
	}
}

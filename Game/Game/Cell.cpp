#include "stdafx.h"
#include "Cell.h"


Cell::Cell()
{
	listOfObjects = DBG_NEW std::map<int, GameObject*>();
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

std::map<int, GameObject*>* Cell::getAllObjects()
{
	if (listOfObjects) {
		return listOfObjects;
	}
	else {
		return NULL;
	}
}

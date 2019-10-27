#include "stdafx.h"
#include "Cell.h"


Cell::Cell()
{
	listOfObjects = new std::map<int, GameObject*>();
}


Cell::~Cell()
{
	//for (list<BaseObject*>::const_iterator it = listOfObjects.begin(); it != listOfObjects.end(); ++it)
	//{
	//	delete *it;
	//}
	//listOfObjects.clear();
}

void Cell::add(int id, GameObject * object)
{
	listOfObjects->insert(std::pair<int, GameObject*>(id, object));
}

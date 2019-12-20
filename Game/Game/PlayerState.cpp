#include "stdafx.h"
#include "PlayerState.h"

vector<AppleBullet*>* PlayerState::getListBullet() { return &list; }

void PlayerState::deleteAppleBullet() {
	if (list.size() != 0) {
		for (int i = 0; i < list.size(); i++)
		{
			if (list.at(i)->getIsDead()) {
				delete list.at(i);
				list.at(i) = nullptr;
				list.erase(list.begin() + i);
			}
		}
	}
}

#include "stdafx.h"
#include "BulletBoss.h"

BulletBoss::BulletBoss(float x, float y, float width, float height, Tag tag) : GameObject(x, y, width, height, tag) {
	isDead = false;
}

BulletBoss::~BulletBoss() {

}

Box BulletBoss::GetBoundingBox() {
	Box box;

	box.x = x;
	box.y = y;
	box.width = width;
	box.height = height;
	box.vx = vx;
	box.vy = vy;

	return box;
}

D3DXVECTOR2 BulletBoss::getVelocity() {
	D3DXVECTOR2 result(vx, vy);
	return result;
}

bool BulletBoss::getIsDead() { 
	return isDead;
}


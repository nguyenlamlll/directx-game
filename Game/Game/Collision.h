#pragma once
struct Box {
	// Possition of top-left corner
	float x, y;

	// Dimensions
	float width;
	float height;

	// Velocity
	float vx, vy;
};

enum CollisionSide
{
	Left,
	Top,
	Right,
	Bottom,
	Unknown
};

struct CollisionResult
{
	bool isCollide;
	float entryTime;
	int sideX, sideY;
	CollisionSide sideCollided;
	CollisionResult() { isCollide = false; entryTime = 1.0f; sideX = sideY = 0; sideCollided = CollisionSide::Unknown; }
};

class Collision
{
private:
	static Collision* instance;
public:
	static Collision * getInstance();

	// Return a float (from 0.0 to 1.0) that prepresents the time when the collision happens.
	// 0.0 is the beginning time. 1.0 is the ending time.
	// For example:
	//		If the function returns 1.0, it means there is no collision.
	//		If the functions returns 0.5, it means collision happens in the middle of the on-going path.
	CollisionResult SweptAABB(Box b1, Box b2, float& normalX, float& normalY, float deltaTime);

	Box GetSweptBroadphaseBox(Box b, float deltaTime);

	bool AABBCheck(Box b1, Box b2);

	bool willCollide(Box box, Box block, float &returnCollisionTime);
};


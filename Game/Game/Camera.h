#pragma once
#include "Global.h"
#include "Collision.h"

class Player;
class Camera
{
private:
	static Camera* instance;
	Camera();

	int m_width;
	int m_height;

	// Position of the camera is the center of the camera view.
	D3DXVECTOR2 m_position;

	// Boundary of camera to the left. Camera won't go any further to the left past this line.
	float m_leftBoundary{ - 1000 };
	// Boundary of camera to the right. Camera won't go any further to the right past this line.
	float m_rightBoundary{ 5000 };
	// Top boundary. Camera won't go higher this line.
	float m_topBoundary{ -1000 };
	// Bottom boundary. Camera won't go below this line.
	float m_bottomBoundary{ 5000 };

	Player* m_player;

public:
	static Camera * getInstance();

	void attachPlayer(Player* player);

	int getWidth() { return m_width; }
	int getHeight() { return m_height; }

	D3DXVECTOR2 getPosition() { return m_position; }
	void setPosition(D3DXVECTOR2 newPosition)
	{
		m_position = newPosition;
		updateCamera();
	}

	RECT getBound();
	Box getBox();

	void updateCamera();

	D3DXVECTOR4 getBoundaries();
	void setBoundaries(float left, float right, float top, float bottom);
};


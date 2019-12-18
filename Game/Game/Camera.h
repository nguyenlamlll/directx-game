#pragma once
#include "Global.h"
#include "Collision.h"

class Camera
{
private:
	static Camera* instance;
	Camera();

	int m_width;
	int m_height;

	// Position of the camera is the center of the camera view.
	D3DXVECTOR2 m_position;

public:
	static Camera * getInstance();

	int getWidth() { return m_width; }
	int getHeight() { return m_height; }

	D3DXVECTOR2 getPosition() { return m_position; }
	void setPosition(D3DXVECTOR2 newPosition)
	{
		m_position = newPosition;
		updateCamera(newPosition);
	}

	RECT getBound();
	Box getBox();

	void updateCamera(D3DXVECTOR2 playerPosition);
};


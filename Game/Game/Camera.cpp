#include "stdafx.h"
#include "Camera.h"

Camera* Camera::instance = nullptr;
Camera::Camera()
{
	m_position.x = (Global::GetInstance()->g_ScreenWidth / 2);
	m_position.y = (Global::GetInstance()->g_ScreenHeight / 2); //+ Global::GetInstance()->g_GameUIArea / 2);
	m_width = Global::GetInstance()->g_ScreenWidth;
	m_height = Global::GetInstance()->g_ScreenHeight; // - Global::GetInstance()->g_GameUIArea;
}
Camera* Camera::getInstance()
{
	if (instance)
	{
		return instance;
	}
	else
	{
		instance = new Camera();

		return instance;
	}
}

RECT Camera::getBound()
{
	RECT bound;

	bound.left = m_position.x - m_width / 2;
	bound.right = bound.left + m_width;
	bound.top = m_position.y - m_height / 2;
	bound.bottom = bound.top + m_height;

	return bound;
}

Box Camera::getBox()
{
	Box box;
	box.x = m_position.x - m_width / 2;
	box.y = m_position.y - m_height / 2;
	box.width = m_width;
	box.height = m_height;
	box.vx = box.vy = 0;

	return box;
}

void Camera::updateCamera(D3DXVECTOR2 playerPosition)
{
	if (m_position.y >= 1463.75)
	{
		m_position.y = 1463.75;
	}

	//if (m_position.x + GLOBAL->g_ScreenWidth / 2 >= GLOBAL->g_WorldMapWidth)
	//{
	//	//Set camera position to end of map
	//	m_position.x = GLOBAL->g_WorldMapWidth - GLOBAL->g_ScreenWidth / 2;
	//}
	//if (m_position.x - GLOBAL->g_ScreenWidth / 2 < 0)
	//{
	//	//Set camera position to the first
	//	m_position.x = GLOBAL->g_ScreenWidth / 2;
	//}


	// Hard-coded to not let camera goes below the map
	//if (m_position.y <= 0) // Global::GetInstance()->g_WorldMapHeight/2)
	//{
	//	m_position.y = 0; //GLOBAL->g_WorldMapHeight - GLOBAL->g_ScreenHeight / 2;
	//}

	// If the camera goes up and hit the map boundary.
	//if (m_position.y >= Global::GetInstance()->g_ScreenHeight / 2)
	//{
	//	m_position.y = Global::GetInstance()->g_ScreenHeight / 2;
	//}
}

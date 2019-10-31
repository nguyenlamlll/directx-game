#include "stdafx.h"
#include "Camera.h"

Camera* Camera::instance = nullptr;
Camera::Camera()
{
	m_position.x = Global::GetInstance()->g_ScreenWidth / 2;
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

void Camera::updateCamera()
{
}

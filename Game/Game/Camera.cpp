#include "stdafx.h"
#include "Camera.h"
#include "Player.h"
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

void Camera::attachPlayer(Player * player)
{
	m_player = player;
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
	if (m_position.x <= m_leftBoundary)
	{
		m_position.x = m_leftBoundary;
	}
	if (m_position.x > m_leftBoundary && m_position.x <= (m_leftBoundary + 10))
	{
		m_position = (D3DXVECTOR2(m_player->getPosition().x + 74, m_position.y));
	}

	if (m_position.x >= m_rightBoundary)
	{
		m_position.x = m_rightBoundary;
	}
	if (m_position.x < m_rightBoundary && m_position.x >= (m_rightBoundary - 10))
	{
		m_position = (D3DXVECTOR2(m_player->getPosition().x - 74, m_position.y));
	}

	if (m_position.y <= m_topBoundary)
	{
		m_position.y = m_topBoundary;
	}
	if (m_position.y >= m_bottomBoundary)
	{
		m_position.y = m_bottomBoundary;
	}

}

// Return a vector 4 of boundaries in this order: left, right, top, bottom.
D3DXVECTOR4 Camera::getBoundaries()
{
	return D3DXVECTOR4(
		m_leftBoundary,
		m_rightBoundary,
		m_topBoundary,
		m_bottomBoundary
	);
}

void Camera::setBoundaries(float left, float right, float top, float bottom)
{
	m_leftBoundary = left;
	m_rightBoundary = right;
	m_topBoundary = top;
	m_bottomBoundary = bottom;
}

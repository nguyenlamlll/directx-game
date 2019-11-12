#include "stdafx.h"
#include "Animation.h"

Animation::Animation(LPCWSTR filePath, int totalFrames, int rows, int columns, bool infinite, float timePerFrame)
	: Sprite(filePath)
{
	m_columns = columns;
	m_rows = rows;
	m_curIndex = m_curCol = m_curRow = m_curTotalTime = 0;
	m_frameWidth = m_textureWidth / columns;
	m_frameHeight = m_textureHeight / rows;

	// Set texture width/height to frame wid/height
	m_textureWidth = m_frameWidth;
	m_textureHeight = m_frameHeight;

	m_totalFrames = totalFrames;
	m_timePerFrame = timePerFrame;
	m_infiniteAnim = infinite;

	// Set source rect for texture
	m_rect.left = 0;
	m_rect.top = 0;
	m_rect.right = m_frameWidth;
	m_rect.bottom = m_frameHeight;
	m_sourceRect = m_rect;
	m_flipHorizontal = true;
	m_isFinished = false;
}


Animation::~Animation()
{
}

void Animation::Update(float deltaTime)
{
	// no update when the number of frames are less than 1
	if (m_totalFrames <= 1)
	{
		m_isFinished = true;
		return;
	}
	//update frame
	if (m_curTotalTime >= m_timePerFrame)
	{
		m_curTotalTime = 0;

		if (m_curIndex >= m_totalFrames) //is finished
		{
			m_isFinished = true;
		}
		else
		{
			m_rect.left = (m_curIndex % m_columns)*m_frameWidth;
			m_rect.top = (m_curIndex%m_rows) * m_frameHeight;
			m_rect.right = m_rect.left + m_frameWidth;
			m_rect.bottom = m_rect.top + m_frameHeight;
			//Set sourceRect
			m_sourceRect = m_rect;
		}
		//increase current index
		if (m_infiniteAnim)
		{
			m_curIndex = (m_curIndex + 1) % m_totalFrames;
		}
		else
		{
			m_curIndex++;
		}
	}
	else
	{
		m_curTotalTime += deltaTime;
	}
}

void Animation::Reset()
{
	m_curCol = m_curIndex = m_curRow = 0;
	m_rect.left = 0;
	m_rect.top = 0;
	m_rect.right = m_frameWidth;
	m_rect.bottom = m_frameHeight;
	m_sourceRect = m_rect;
	m_isFinished = false;
}

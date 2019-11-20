#pragma once
#include "Sprite.h"

class Animation : public Sprite
{
private:
	int	m_columns;
	int	m_rows;
	int	m_curIndex;
	int	m_curCol;
	int	m_curRow;
	int	m_frameWidth;
	int	m_frameHeight;
	int	m_totalFrames;
	float m_timePerFrame;
	float m_curTotalTime;
	bool m_infiniteAnim;
	RECT m_rect;
	bool m_isFinished;

public:
	Animation(LPCWSTR filePath, int totalFrames, int rows, int columns, bool infinite = true, float timePerFrame = 0.1f);
	~Animation();

	void Update(float deltaTime);

	void Reset();

	bool getIsFinished();
};


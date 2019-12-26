#include "stdafx.h"
#include "AladdinGlobal.h"

AladdinGlobal* AladdinGlobal::m_instance = nullptr;
AladdinGlobal * AladdinGlobal::getInstance()
{
	if (m_instance)
	{
		return m_instance;
	}
	else
	{
		m_instance = new AladdinGlobal();
		return m_instance;
	}
}

void AladdinGlobal::setHealth(int value)
{
	m_health = value;
}

int AladdinGlobal::getHealth()
{
	return m_health;
}

void AladdinGlobal::setScores(int value)
{
	m_scores = value;
}

int AladdinGlobal::getScores()
{
	return m_scores;
}

void AladdinGlobal::setLifeCount(int value)
{
	m_lifeCount = value;
}

int AladdinGlobal::getLifeCount()
{
	return m_lifeCount;
}

void AladdinGlobal::setAppleCount(int value)
{
	m_appleCount = value;
}

int AladdinGlobal::getAppleCount()
{
	return m_appleCount;
}

void AladdinGlobal::setRubyCount(int value)
{
	m_rubyCount = value;
}

int AladdinGlobal::getRubyCount()
{
	return m_rubyCount;
}

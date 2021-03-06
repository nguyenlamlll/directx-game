#include "stdafx.h"
#include "Health.h"

Health::Health(float maximumHealth)
	: Health(maximumHealth, maximumHealth)
{
}

Health::Health(float currentHealth, float maximumHealth)
{
	m_currentHealth = currentHealth;
	m_maximumHealth = maximumHealth;
}

Health::~Health()
{
}

void Health::takeDamage(float damage)
{
	m_currentHealth -= damage;
}

void Health::recover(float amount)
{
	m_currentHealth += amount;
}

float Health::getCurrentHealth()
{
	return m_currentHealth;
}

void Health::setCurrentHealth(float value)
{
	m_currentHealth = value;
}

float Health::getMaximumHealth()
{
	return m_maximumHealth;
}

void Health::setMaximumHealth(float value)
{
	m_maximumHealth = value;
}

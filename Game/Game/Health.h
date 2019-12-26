#pragma once
class Health
{
protected:
	float m_currentHealth;
	float m_maximumHealth;

public:
	Health(float maximumHealth);
	Health(float currentHealth, float maximumHealth);
	~Health();

	// Subtract current health of this object with the amount of damage passed to the function.
	void takeDamage(float damage);

	// Add to current health of this object with the recovery amount passed to the function.
	void recover(float amount);

	float getCurrentHealth();
	void setCurrentHealth(float value);

	float getMaximumHealth();
	void setMaximumHealth(float value);
};


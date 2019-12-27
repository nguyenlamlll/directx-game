#pragma once
class AladdinGlobal
{
private:
	static AladdinGlobal* m_instance;

public:
	static AladdinGlobal* getInstance();

private:
	int m_health{ 9 };
	int m_scores{ 1000 };
	int m_lifeCount{ 4 };
	int m_appleCount{ 15 };
	int m_rubyCount{ 10 };

	D3DXVECTOR2 m_lastCheckpoint = D3DXVECTOR2(0,0);

public:
	void setHealth(int value);
	int getHealth();

	void setScores(int value);
	int getScores();

	void setLifeCount(int value);
	int getLifeCount();

	void setAppleCount(int value);
	int getAppleCount();

	void setRubyCount(int value);
	int getRubyCount();

	void setLastCheckpoint(D3DXVECTOR2 value);
	D3DXVECTOR2 getLastCheckpoint();
};


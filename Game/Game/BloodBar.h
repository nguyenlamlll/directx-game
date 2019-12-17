#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Sprite.h"
#include "Player.h"

class BloodBar : public GameObject
{
protected:
	Animation* m_image;
	Animation* m_imageHealth1;
	Animation* m_imageHealth2;
	Animation* m_imageHealth3;
	Animation* m_imageHealth4;
	Animation* m_imageHealth5;
	Animation* m_imageHealth7;
	Animation* m_imageHealth9;

	Player* m_player;

	int healthCurrent;

public:
	BloodBar(float x, float y, float width, float height);
	~BloodBar();

	void Update(float deltaTime);
	void Draw();

	void changeImage();
	
	void attachPlayer(Player* player);
};


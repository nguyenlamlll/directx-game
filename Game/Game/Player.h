#pragma once
#include "GameObject.h"
#include "Sprite.h";
#include "Input.h"

class Player : public GameObject
{
private:
	Sprite* m_playerSprite;
	ControlDevice m_controlDevice{ ControlDevice::Keyboard };
	float speed;
public:
	Player(float x, float y, float width, float height, LPCWSTR spritePath);
	~Player();

	void SetControlDevice(ControlDevice device);

	Box GetBoundingBox();

	D3DXVECTOR2 getVelocity();

	void Update(float deltaTime);
	void Draw();
};


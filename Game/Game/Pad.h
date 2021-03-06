#pragma once
#include "GameObject.h"
#include "Sprite.h";
#include "Input.h"

class Pad : public GameObject
{
private:
	Sprite* m_padSprite;
	ControlDevice m_controlDevice;
	float speed;
public:
	Pad(float x, float y, float width, float height, LPCWSTR spritePath);
	~Pad();

	void SetControlDevice(ControlDevice device);

	Box GetBoundingBox();

	D3DXVECTOR2 getVelocity();

	void Update(float deltaTime);
	void Draw();
};


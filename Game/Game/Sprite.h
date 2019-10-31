#pragma once

#include "stdafx.h"
#include "Global.h"
#include "Camera.h"
class Sprite
{
private:
	LPDIRECT3DTEXTURE9 m_texture;
	LPD3DXSPRITE m_sprite;

	D3DXVECTOR3 m_position;
	D3DCOLOR color;
	bool initialized;

	int m_textureWidth;
	int m_textureHeight;

	bool m_flipHorizontal{ false };
	bool m_flipVertical{ false };

public:
	Sprite();
	Sprite(LPCWSTR file);
	~Sprite();

	void setPositionX(float value) {
		m_position.x = value;
	}
	void setPositionY(float value) {
		m_position.y = value;
	}
	float getPositionX() {
		return m_position.x;
	}
	float getPositionY() {
		return m_position.y;
	}

	void setFlipHorizontal(bool value) { m_flipHorizontal = value; }
	void setFlipVertical(bool value) { m_flipVertical = value; }
	bool getFlipHorizontal() { return m_flipHorizontal; }
	bool getFlipVertical() { return m_flipVertical; }

	void Draw();
};

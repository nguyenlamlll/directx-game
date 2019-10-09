#pragma once

#include "stdafx.h"
#include "Global.h"

class Sprite
{
private:
	LPDIRECT3DTEXTURE9 m_texture;
	LPD3DXSPRITE m_sprite;

	D3DXVECTOR3 m_position;
	D3DCOLOR color;
	bool initialized;

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

	void Draw();
};

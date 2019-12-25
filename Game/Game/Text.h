#pragma once
#include "Global.h"
class Text
{
private:
	LPD3DXFONT m_fontHandler;

	LPCWSTR m_text;
	LPCWSTR m_font;

	int m_fontHeight;
	D3DXVECTOR2 m_position;
	D3DCOLOR m_color;
	bool m_isItalic;
	DWORD m_format;

public:
	Text(LPCWSTR text, LPCWSTR font, int fontHeight, D3DXVECTOR2 position, D3DXCOLOR color, bool isItalic, bool isSingle);
	~Text();

	void draw();

	void setText(LPCWSTR text);
	LPCWSTR getText();

	void setColor(D3DCOLOR color);
	D3DCOLOR getColor();
};


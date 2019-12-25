#include "stdafx.h"
#include "Text.h"


Text::Text(LPCWSTR text, LPCWSTR fontName, int fontHeight, D3DXVECTOR2 position, D3DXCOLOR color, bool isItalic, bool isSingle)
{
	// Create Font
	HRESULT createFontResult = D3DXCreateFont(
		Global::GetInstance()->g_DirectDevice,
		fontHeight,
		0,
		FW_NORMAL,
		1,
		isItalic,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY,
		FF_DONTCARE,
		fontName,
		&m_fontHandler);
	if (FAILED(createFontResult))
	{
		MessageBox(NULL, L"Cannot create font handler", L"Error", MB_OK);
	}

	this->m_text = text;
	this->m_fontHeight = fontHeight;
	this->m_color = color;
	this->m_isItalic = isItalic;

	if (isSingle)
		this->m_format = DT_LEFT | DT_NOCLIP;
	else
		this->m_format = DT_LEFT | DT_WORDBREAK;

	this->m_position = position;

}


Text::~Text()
{
}

void Text::draw()
{
	RECT rect;
	SetRect(&rect, (int)m_position.x, (int)m_position.y, (int)m_position.x, (int)m_position.y);

	m_fontHandler->DrawText(
		Global::GetInstance()->g_SpriteHandler,
		m_text,
		-1,
		&rect,
		this->m_format,
		this->m_color
	);
}

void Text::setText(LPCWSTR text)
{
	m_text = text;
}

LPCWSTR Text::getText()
{
	return m_text;
}

void Text::setColor(D3DCOLOR color)
{
	m_color = color;
}

D3DCOLOR Text::getColor()
{
	return m_color;
}


#include "stdafx.h"
#include "Sprite.h"

Sprite::Sprite()
{
	//Default the m_sprite to m_position (0, 0, 0)
	m_position.x = 0;
	m_position.y = 0;
	m_position.z = 0;

	//When color is set to white, what you see is exactly what the image looks like.
	color = D3DCOLOR_ARGB(255, 255, 255, 255);

	//We are not initialized yet
	initialized = false;
}

Sprite::Sprite(LPCWSTR filePath)
{
	//Default the m_sprite to m_position (0, 0, 0)
	m_position.x = 0;
	m_position.y = 0;
	m_position.z = 0;

	//When color is set to white, what you see is exactly what the image looks like.
	color = D3DCOLOR_ARGB(255, 255, 255, 255);

	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(filePath, &info);
	if (result != D3D_OK)
	{
		DebugHelper::DebugOut(L"[ERROR] GetImageInfoFromFile failed: %s\n", filePath);
		return;
	}

	result = D3DXCreateTextureFromFileEx(
		Global::GetInstance()->g_DirectDevice,	// Pointer to Direct3D device object
		filePath,								// Path to the image to load
		info.Width,								// Texture width
		info.Height,							// Texture height
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 255, 255),			// Transparent color
		&info,
		NULL,
		&m_texture);								// Created texture pointer

	if (result != D3D_OK)
	{
		OutputDebugString(L"[ERROR] CreateTextureFromFile failed\n");
		return;
	}

	DebugHelper::DebugOut(L"[INFO] Texture loaded Ok: %s \n", filePath);

	m_sprite = GLOBAL->g_SpriteHandler;

	////Same functionality as D3DXCreateTextureFromFile EXCEPT width and height are manually entered
	//if (!SUCCEEDED(D3DXCreateTextureFromFileEx(
	//	device, 
	//	file.c_str(),
	//	width, 
	//	height, 
	//	D3DX_DEFAULT, 
	//	0, 
	//	D3DFMT_UNKNOWN, 
	//	D3DPOOL_MANAGED, 
	//	D3DX_DEFAULT,
	//	D3DX_DEFAULT, 
	//	0, 
	//	NULL, 
	//	NULL, 
	//	&m_texture)))
	//{
	//	std::wstring fileStr(file);
	//	std::wstring output = "There was an issue creating the Texture.  Make sure the requested image is available.  Requested image: " + fileStr;
	//	MessageBox(NULL, output.c_str(), NULL, NULL);
	//	return false;
	//}

	////Attempt to create the m_sprite
	//if (!SUCCEEDED(D3DXCreateSprite(device, &m_sprite)))
	//{
	//	MessageBox(NULL, L"There was an issue creating the Sprite.", NULL, NULL);
	//}
}

void Sprite::Draw()
{
	if (m_sprite && m_texture)
	{
		m_sprite->Begin(D3DXSPRITE_ALPHABLEND);

		m_sprite->Draw(m_texture, NULL, NULL, &m_position, color);

		m_sprite->End();
	}
}

Sprite::~Sprite()
{
	if (m_sprite)
	{
		m_sprite->Release();
		m_sprite = 0;
	}

	if (m_texture)
	{
		m_texture->Release();
		m_texture = 0;
	}
}
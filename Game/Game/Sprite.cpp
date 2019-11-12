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

	m_textureWidth = info.Width;
	m_textureHeight = info.Height;

	m_sourceRect.left = 0;
	m_sourceRect.right = info.Width;
	m_sourceRect.top = 0;
	m_sourceRect.bottom = info.Height;

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

	m_center = D3DXVECTOR3((float)m_textureWidth / 2, (float)m_textureHeight / 2, 0);;
}

void Sprite::Draw()
{
	if (m_sprite && m_texture)

	{
		//m_sprite->Begin(D3DXSPRITE_ALPHABLEND);

		//m_sprite->Draw(m_texture, NULL, NULL, &m_position, color);

		D3DXMATRIX mt;
		D3DXMatrixIdentity(&mt);
		//mt._22 = -1.0f;
		//mt._11 = mt._33 = mt._44 = 1.0f;
		mt._41 = -(float)(Camera::getInstance()->getPosition().x - GLOBAL->g_ScreenWidth / 2);
		mt._42 = -(float)(Camera::getInstance()->getPosition().y - GLOBAL->g_ScreenHeight/2);

		D3DXVECTOR4 transformedPos;
		D3DXVECTOR3 drawingPosition((float)m_position.x, (float)m_position.y, 0);
		D3DXVec3Transform(&transformedPos, &drawingPosition, &mt);

		D3DXVECTOR3 p = { transformedPos.x, transformedPos.y, 0 };
		//D3DXVECTOR3 center((float)m_textureWidth / 2, (float)m_textureHeight / 2, 0);

		D3DXMATRIX old, m; //temp var
		Global::GetInstance()->g_SpriteHandler->GetTransform(&old); //Save the old matrix
		//Flip image if exist
		if (m_flipHorizontal)
		{
			D3DXMatrixScaling(&m, -1, 1, 1);
			p.x *= -1.0f;
			Global::GetInstance()->g_SpriteHandler->SetTransform(&m);
		}
		if (m_flipVertical)
		{
			D3DXMatrixScaling(&m, 1, -1, 1);
			p.y *= -1.0f;
			Global::GetInstance()->g_SpriteHandler->SetTransform(&m);
		}

		m_sprite->Draw(
			m_texture, 
			&m_sourceRect, 
			&m_center,
			&p,
			color);

		//Reset to old matrix
		Global::GetInstance()->g_SpriteHandler->SetTransform(&old);

		//m_sprite->End();
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
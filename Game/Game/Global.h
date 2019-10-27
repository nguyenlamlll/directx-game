#pragma once

#define CLASS_NAME				L"Game Project Class"
#define GAME_TITLE				L"Game Project"
#define GLOBAL					Global::GetInstance()
#define KEYBOARD_BUFFER_SIZE	1024
#define FRAME_PER_SEC			60.0f

#define MAP_WIDTH 2720
#define MAP_HEIGHT 2720

class Global
{
private:
	static Global*		_instance;
public:
	static Global*		GetInstance();

	HINSTANCE			g_hInstance = NULL;			//hInstance of the game
	HWND				g_HWND;				//HWND of the game
	bool				g_IsWindowed = true;		//true if windowed
	int					g_ScreenWidth = 640;
	int					g_ScreenHeight = 320;
	LPDIRECT3DDEVICE9	g_DirectDevice = NULL;		//Direct X device
	LPD3DXSPRITE		g_SpriteHandler = NULL;		//Direct X Sprite handler
	LPDIRECT3DSURFACE9	g_BackBuffer = NULL;		//Back buffer
	int					g_GameUIArea = 0;				//game ui start m_position
	int					g_WorldMapWidth;
	int					g_WorldMapHeight;
	int					g_Scene1_EndMap = 2000;
	int					g_Scene2_EndMap = 240;
	int					g_ChangeScene_Delay = 3.0f;

	const UINT			g_MapWidth = MAP_WIDTH;
	const UINT			g_MapHeight = MAP_HEIGHT;
};
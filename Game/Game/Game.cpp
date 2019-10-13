#include "stdafx.h"
#include "Game.h"


#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"00 - Intro"

#define BRICK_TEXTURE_PATH L"brick.png"
#define PAD_TEXTURE_PATH L"Resources\\pad.png"
#define BALL_TEXTURE_PATH L"Resources\\ball.png"
#define LEFT_WIN_TEXTURE_PATH L"Resources\\LeftWon.png"
#define RIGHT_WIN_TEXTURE_PATH L"Resources\\RightWon.png"
#define NEW_MATCH_TEXTURE_PATH L"Resources\\NewMatch.png"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 255)
#define SCREEN_WIDTH Global::GetInstance()->g_ScreenWidth
#define SCREEN_HEIGHT Global::GetInstance()->g_ScreenHeight

#define MAX_FRAME_RATE 60


//LPDIRECT3D9 d3d = NULL;						// Direct3D handle
//LPDIRECT3DDEVICE9 d3ddv = NULL;				// Direct3D device object
//
//LPDIRECT3DSURFACE9 backBuffer = NULL;
//LPD3DXSPRITE spriteHandler = NULL;			// Sprite helper library to help us draw 2D image on the screen 
//
LPDIRECT3DTEXTURE9 texBrick;				// texture object to store brick image

int brick_x = 0;
int brick_y = 0;


/*
	Load all game resources.
*/
void Game::LoadResources()
{
	m_rightPadSprite = new Sprite(PAD_TEXTURE_PATH);
	m_rightPadSprite->setPositionX(SCREEN_WIDTH - 50);
	m_rightPadSprite->setPositionY(SCREEN_HEIGHT / 2);

	m_leftPadSprite = new Sprite(PAD_TEXTURE_PATH);
	m_leftPadSprite->setPositionX(20);
	m_leftPadSprite->setPositionY(SCREEN_HEIGHT / 2);

	m_ballSprite = new Sprite(BALL_TEXTURE_PATH);
	m_ballSprite->setPositionX(SCREEN_WIDTH / 2);
	m_ballSprite->setPositionY(SCREEN_HEIGHT / 2);


	m_newMatchSprite = new Sprite(NEW_MATCH_TEXTURE_PATH);
	m_newMatchSprite->setPositionX(-1000);
	m_newMatchSprite->setPositionY(SCREEN_HEIGHT / 2 + 50);

	m_leftWinSprite = new Sprite(LEFT_WIN_TEXTURE_PATH);
	m_leftWinSprite->setPositionX(-1000);
	m_leftWinSprite->setPositionY(SCREEN_HEIGHT / 2);

	m_rightWinSprite = new Sprite(RIGHT_WIN_TEXTURE_PATH);
	m_rightWinSprite->setPositionX(-1000);
	m_rightWinSprite->setPositionY(SCREEN_HEIGHT / 2);

}

void Game::setDefaultSpritePositions()
{
	m_rightPadSprite->setPositionX(SCREEN_WIDTH - 50);
	m_rightPadSprite->setPositionY(SCREEN_HEIGHT / 2);

	m_leftPadSprite->setPositionX(20);
	m_leftPadSprite->setPositionY(SCREEN_HEIGHT / 2);

	m_ballSprite->setPositionX(SCREEN_WIDTH / 2);
	m_ballSprite->setPositionY(SCREEN_HEIGHT / 2);

	m_newMatchSprite->setPositionX(-1000);
	m_newMatchSprite->setPositionY(SCREEN_HEIGHT / 2 + 50);
	m_leftWinSprite->setPositionX(-1000);
	m_leftWinSprite->setPositionY(SCREEN_HEIGHT / 2);
	m_rightWinSprite->setPositionX(-1000);
	m_rightWinSprite->setPositionY(SCREEN_HEIGHT / 2);
}

int Game::InitWindow()
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbClsExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = GLOBAL->g_hInstance;
	wc.lpfnWndProc = WinProc;
	wc.lpszClassName = CLASS_NAME;
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wc);
	DWORD style;
	if (GLOBAL->g_IsWindowed) {
		style = WS_OVERLAPPEDWINDOW;
	}
	else
	{
		style = WS_EX_TOPMOST | WS_POPUP;
	}

	HWND hwnd = CreateWindow(
		CLASS_NAME,
		GAME_TITLE,
		style,
		CW_USEDEFAULT, CW_USEDEFAULT,
		GLOBAL->g_ScreenWidth,
		GLOBAL->g_ScreenHeight,
		NULL, NULL,
		GLOBAL->g_hInstance,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, L"Failed to create Window", L"Error", MB_OK);
		return 0;
	}
	GLOBAL->g_HWND = hwnd;
	//Sound::create(hwnd);
	ShowWindow(hwnd, _nCmdShow);
	return 1;
}

int Game::InitDirectX()
{
	LPDIRECT3D9 d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (d3d != NULL)
	{
		//GlobalVar::SetDirect3D(d3d);
	}
	else
	{
		MessageBox(NULL, L"Failed to create Direct3D", L"Error", MB_OK);
		return 0;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = GLOBAL->g_ScreenWidth;
	d3dpp.BackBufferHeight = GLOBAL->g_ScreenHeight;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;//D3DFMT_A8B8G8R8;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = GLOBAL->g_HWND;
	d3dpp.Windowed = GLOBAL->g_IsWindowed;


	LPDIRECT3DDEVICE9 dev;
	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		GLOBAL->g_HWND,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&dev
	);
	if (dev == NULL)
	{
		MessageBox(NULL, L"Failed to create Direct3D Device", L"Error", MB_OK);
		return 0;
	}
	GLOBAL->g_DirectDevice = dev;

	//Create Sprite
	LPD3DXSPRITE sprite;
	if (FAILED(D3DXCreateSprite(GLOBAL->g_DirectDevice, &sprite)))
	{
		MessageBox(NULL, L"Cannot create sprite", L"Error", MB_OK);
		return 0;
	}
	GLOBAL->g_SpriteHandler = sprite;

	//Get back buffer
	LPDIRECT3DSURFACE9 backbuffer;
	if (FAILED(dev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer)))
	{
		MessageBox(NULL, L"Cannot create Back Buffer", L"Error", MB_OK);
		return 0;
	}
	GLOBAL->g_BackBuffer = backbuffer;
	return 1;
}

int Game::InitKeyboard()
{
	return 0;
}

LRESULT Game::WinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		//SCENES->GetCurrentScene()->OnKeyDown(wParam);
		KeyboardInput::GetInstance()->keyDown(wParam);
		break;
	case WM_KEYUP:
		//SCENES->GetCurrentScene()->OnKeyUp(wParam);
		KeyboardInput::GetInstance()->keyUp(wParam);
		break;


	case WM_LBUTTONDOWN:
		MouseInput::getInstance()->leftMouseButtonDown(hwnd);
		break;

	case WM_MOUSEMOVE:
	{
		MouseInput::getInstance()->mouseMove(hwnd, lParam);
		break;
	}
	case WM_LBUTTONUP:
		MouseInput::getInstance()->leftMouseButtonUp();
		break;

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}

D3DXVECTOR3 m_position((float)brick_x, (float)brick_y, 0);
bool isTopLeft = true, isTopRight = false, isBottomLeft = false, isBottomRight = false;
#define SPEED 0.05
#define SPACING_FROM_BORDER 20
void MoveBrickAroundCorners(float dt)
{
	if (isTopLeft) {
		m_position.x += SPEED * dt;
	}
	else if (isTopRight) {
		m_position.y += SPEED * dt;
	}
	else if (isBottomRight) {
		m_position.x -= SPEED * dt;
	}
	else {
		m_position.y -= SPEED * dt;
	}

	if (m_position.x >= SCREEN_WIDTH - SPACING_FROM_BORDER && m_position.y == 0) {
		m_position.x = SCREEN_WIDTH - SPACING_FROM_BORDER;
		m_position.y = 0;
		isTopRight = true;

		isBottomRight = false;
		isBottomLeft = false;
		isTopLeft = false;
		return;
	}
	if (m_position.x >= SCREEN_WIDTH - SPACING_FROM_BORDER && m_position.y >= SCREEN_HEIGHT - SPACING_FROM_BORDER) {
		m_position.x = SCREEN_WIDTH - SPACING_FROM_BORDER;
		m_position.y = SCREEN_HEIGHT - SPACING_FROM_BORDER;
		isBottomRight = true;

		isTopRight = false;
		isBottomLeft = false;
		isTopLeft = false;
		return;
	}
	if (m_position.x <= 0 && m_position.y >= SCREEN_HEIGHT - SPACING_FROM_BORDER) {
		m_position.x = 0;
		m_position.y = SCREEN_HEIGHT - SPACING_FROM_BORDER;
		isBottomLeft = true;

		isTopRight = false;
		isBottomRight = false;
		isTopLeft = false;
		return;
	}
	if (m_position.x == 0 && m_position.y <= 0) {
		m_position.x = 0;
		m_position.y = 0;
		isTopLeft = true;

		isBottomLeft = false;
		isBottomRight = false;
		isTopRight = false;
		return;
	}
}

float ballSpeed = 0.f;
float ballVerticalSpeed = 0.f;
bool isMovingRight = true;
bool isLeftMovingUp = false;
bool isLeftMovingDown = false;
bool isRightMovingUp = false;
bool isRightMovingDown = false;
bool isRoundPlaying = true;
bool isLeftWon = false;

/*
	Update game status for this frame.
	dt: Time period between beginning of last frame and beginning of this frame
*/
void Game::GameUpdate(float dt)
{
	// Check if round is finished.
	if (m_ballSprite->getPositionX() >= SCREEN_WIDTH) {
		isRoundPlaying = false;
		isLeftWon = true;
	}
	if (m_ballSprite->getPositionX() <= 0) {
		isRoundPlaying = false;
		isLeftWon = false;
	}
	if (!isRoundPlaying) {
		if (isLeftWon) {
			m_leftWinSprite->setPositionX(60);
		}
		else {
			m_rightWinSprite->setPositionX(60);
		}
		m_newMatchSprite->setPositionX(60);
		if (KeyboardInput::GetInstance()->isKeyDown(VK_T)) {
			setDefaultSpritePositions();

			isRoundPlaying = true;
		}
		return;
	}

	// Otherwise, keep running the round.
	if (KeyboardInput::GetInstance()->isKeyDown(VK_W)) {
		isLeftMovingUp = true;
		isLeftMovingDown = false;
		m_leftPadSprite->setPositionY(m_leftPadSprite->getPositionY() - .2f*dt);
	}
	if (KeyboardInput::GetInstance()->isKeyDown(VK_S)) {
		isLeftMovingUp = false;
		isLeftMovingDown = true;
		m_leftPadSprite->setPositionY(m_leftPadSprite->getPositionY() + .2f*dt);
	}

	if (MouseInput::getInstance()->getCurrentMousePosition().y < m_rightPadSprite->getPositionY()) {
		isRightMovingUp = true;
		isRightMovingDown = false;
		m_rightPadSprite->setPositionY(m_rightPadSprite->getPositionY() - .2f*dt);
	}
	if (MouseInput::getInstance()->getCurrentMousePosition().y > m_rightPadSprite->getPositionY()) {
		isRightMovingUp = false;
		isRightMovingDown = true;
		m_rightPadSprite->setPositionY(m_rightPadSprite->getPositionY() + .2f*dt);
	}

	// Move the ball
	if (m_ballSprite->getPositionX() >= m_leftPadSprite->getPositionX()
		|| m_ballSprite->getPositionX() <= m_rightPadSprite->getPositionX()) {
		if (isMovingRight) {
			ballSpeed = 0.3 * dt;
		}
		else {
			ballSpeed = -0.3 * dt;
		}
	}
	if (m_ballSprite->getPositionX() >= SCREEN_WIDTH - 50 - 20) // RIGHT PAD COLLISION HANDLER
	{
		// Check if ball hits pad or hit goal line.
		if (m_ballSprite->getPositionY() > m_rightPadSprite->getPositionY() + 89) // Ball is lower than right pad
		{
			// Let the ball cross right border
			isMovingRight = true;
		}
		else if (m_ballSprite->getPositionY() + 22 < m_rightPadSprite->getPositionY()) // Ball is higher than right pad
		{
			isMovingRight = true;
		}
		else {
			isMovingRight = false;
			if (isRightMovingUp) {
				ballVerticalSpeed = -0.1 * dt;
			}
			if (isRightMovingDown) {
				ballVerticalSpeed = 0.1 * dt;
			}
		}
	}
	else if (m_ballSprite->getPositionX() <= 20 + 40) // LEFT PAD COLLISION HANDLER
	{
		// Check if ball hits pad or hit goal line.
		if (m_ballSprite->getPositionY() > m_leftPadSprite->getPositionY() + 89) // Ball is lower than right pad
		{
			// Let the ball cross right border
			isMovingRight = false;
		}
		else if (m_ballSprite->getPositionY() + 22 < m_leftPadSprite->getPositionY()) // Ball is higher than right pad
		{
			isMovingRight = false;
		}
		else
		{
			isMovingRight = true;
			if (isLeftMovingUp) {
				ballVerticalSpeed = -0.1 * dt;
			}
			if (isLeftMovingDown) {
				ballVerticalSpeed = 0.1 * dt;
			}
		}
	}
	// If ball hits upper border
	if (m_ballSprite->getPositionY() <= 0) {
		ballVerticalSpeed = -ballVerticalSpeed;
	}
	// If ball hits lower border
	if (m_ballSprite->getPositionY() >= SCREEN_HEIGHT - 25) {
		ballVerticalSpeed = -ballVerticalSpeed;
	}
	// Finally, apply.
	m_ballSprite->setPositionX(m_ballSprite->getPositionX() + ballSpeed);
	m_ballSprite->setPositionY(m_ballSprite->getPositionY() + ballVerticalSpeed);


}

/*
	Render a frame
*/
void Game::GameRender()
{
	auto d3ddv = GLOBAL->g_DirectDevice;
	auto spriteHandler = GLOBAL->g_SpriteHandler;
	if (d3ddv->BeginScene())
	{
		// Clear screen (back buffer) with a color
		d3ddv->ColorFill(Global::GetInstance()->g_BackBuffer, nullptr, BACKGROUND_COLOR);
		/*
				spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
				spriteHandler->Draw(texBrick, nullptr, nullptr, &m_position, D3DCOLOR_XRGB(255, 255, 255));
				spriteHandler->End();
				*/

		m_rightPadSprite->Draw();
		m_leftPadSprite->Draw();
		m_ballSprite->Draw();

		if (!isRoundPlaying) {
			m_leftWinSprite->Draw(); 
			m_rightWinSprite->Draw(); 
			m_newMatchSprite->Draw();
		}

		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(nullptr, nullptr, nullptr, nullptr);
}

Game::Game(HINSTANCE hInstance, int nCmdShow)
{
	Global::GetInstance()->g_hInstance = hInstance;
	this->_nCmdShow = nCmdShow;
}

bool Game::GameInit()
{
	if (InitWindow())
	{
		if (!InitDirectX())
			return false;
	}
	else
	{
		return false;
	}

	// TODO: Add scene and start a scene here

	LoadResources();
	return true;
}

void Game::GameRun()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			GameUpdate(dt);
			GameRender();
		}
		else
			Sleep(tickPerFrame - dt);
	}
}

void Game::GameEnd()
{
	// TODO: Finish closing the game here.
}

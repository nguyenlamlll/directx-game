#include "stdafx.h"
#include "MouseInput.h"

MouseInput* MouseInput::instance = nullptr;

MouseInput * MouseInput::getInstance()
{
	if (instance)
	{
		return instance;
	}
	else
	{
		instance = new MouseInput();
		return instance;
	}
}

void MouseInput::leftMouseButtonDown(HWND hwnd)
{
	// Capture mouse input. 

	SetCapture(hwnd);

	// Retrieve the screen coordinates of the client area, 
	// and convert them into client coordinates. 

	GetClientRect(hwnd, &m_rcClient);
	m_ptClientUL.x = m_rcClient.left;
	m_ptClientUL.y = m_rcClient.top;

	// Add one to the right and bottom sides, because the 
	// coordinates retrieved by GetClientRect do not 
	// include the far left and lowermost pixels. 

	m_ptClientLR.x = m_rcClient.right + 1;
	m_ptClientLR.y = m_rcClient.bottom + 1;
	ClientToScreen(hwnd, &m_ptClientUL);
	ClientToScreen(hwnd, &m_ptClientLR);

	// Copy the client coordinates of the client area 
	// to the rcClient structure. Confine the mouse cursor 
	// to the client area by passing the rcClient structure 
	// to the ClipCursor function. 

	SetRect(&m_rcClient, m_ptClientUL.x, m_ptClientUL.y,
		m_ptClientLR.x, m_ptClientLR.y);
	ClipCursor(&m_rcClient);
}

void MouseInput::leftMouseButtonUp()
{
	// Reset the previous line flag, release the mouse cursor, and release the mouse capture. 
	ClipCursor(NULL);
	ReleaseCapture();
}

void MouseInput::mouseMove(HWND hwnd, LPARAM lParam)
{
	// Retrieve a device context (DC) for the client area. 
	HDC hdc; // handle to device context 
	hdc = GetDC(hwnd);

	// Convert the current cursor coordinates to a POINTS structure
	m_currentPosition = MAKEPOINTS(lParam);

#ifdef _DEBUG
	std::wstring raw = L"Mouse: " + std::to_wstring(m_currentPosition.x) + L", " + std::to_wstring(m_currentPosition.y);
	LPCWSTR outputString = raw.c_str();
	OutputDebugString(outputString);
	OutputDebugString(L"\n");
#endif

	ReleaseDC(hwnd, hdc);
}

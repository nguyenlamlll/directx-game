#pragma once
// Reference: https://docs.microsoft.com/en-us/windows/win32/inputdev/using-mouse-input
class MouseInput
{
private:
	static MouseInput* instance;
	
	// Current m_position of the mouse. Relative to the top left corner of the window.
	POINTS m_currentPosition;

	// Client area rectangle 
	RECT m_rcClient;                
	// Client upper left corner 
	POINT m_ptClientUL;    
	// Client lower right corner 
	POINT m_ptClientLR;              
public:
	static MouseInput* getInstance();

	void leftMouseButtonDown(HWND);
	void leftMouseButtonUp();
	void mouseMove(HWND, LPARAM);
	
};


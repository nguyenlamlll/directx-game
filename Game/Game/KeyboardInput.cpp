#include "stdafx.h"
#include "KeyboardInput.h"

KeyboardInput* KeyboardInput::instance = nullptr;

KeyboardInput * KeyboardInput::GetInstance()
{
	if (instance)
	{
		return instance;
	}
	else
	{
		instance = new KeyboardInput();
		return instance;
	}
}

void KeyboardInput::keyDown(WPARAM keyCode)
{
#ifdef _DEBUG
	std::wstring rawKey(getKeyPressedString(keyCode));
	std::wstring raw = rawKey + L" is down.";
	LPCWSTR outputString = raw.c_str();
	OutputDebugString(outputString);
	OutputDebugString(L"\n");
#endif

	// make sure key code is within buffer range
	if (keyCode < InputHelpers::KEYS_ARRAY_LEN)
	{
		keysDown[keyCode] = true;
	}
}

void KeyboardInput::keyUp(WPARAM keyCode)
{
#ifdef _DEBUG
	std::wstring rawKey(getKeyPressedString(keyCode));
	std::wstring raw = rawKey + L" is up.";
	LPCWSTR outputString = raw.c_str();
	OutputDebugString(outputString);
	OutputDebugString(L"\n");
#endif

	// make sure key code is within buffer range
	if (keyCode < InputHelpers::KEYS_ARRAY_LEN)
		// update state table
		keysDown[keyCode] = false;
}

bool KeyboardInput::isKeyDown(UCHAR vKey) const
{
	return keysDown[vKey];
}

bool KeyboardInput::isKeyUp(UCHAR vKey) const
{
	return !keysDown[vKey];
}

LPCWSTR KeyboardInput::getKeyPressedString(UCHAR vKey)
{
	WCHAR name[1024];
	UINT scanCode = MapVirtualKeyW(vKey, MAPVK_VK_TO_VSC);
	LONG lParamValue = (scanCode << 16);
	auto result = GetKeyNameTextW(lParamValue, name, 1024);
	return name;
}
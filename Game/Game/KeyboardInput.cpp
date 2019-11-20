#include "stdafx.h"
#include "KeyboardInput.h"

KeyboardInput* KeyboardInput::instance = nullptr;

KeyboardInput::KeyboardInput()
{
	memset(keysDown, false, sizeof(bool) * InputHelpers::KEYS_ARRAY_LEN);
	memset(m_previousKeysDown, false, sizeof(bool) * InputHelpers::KEYS_ARRAY_LEN);
}

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

// Return true if in the previous frame, key isn't down. But in the current frame, the key is down.
// Meaning, when the user presses a key, the key is triggered one time.
bool KeyboardInput::isKeyTriggered(UCHAR vKey) const
{
	return !m_previousKeysDown[vKey] && keysDown[vKey];
}

bool KeyboardInput::isKeyReleased(UCHAR vKey) const
{
	return m_previousKeysDown[vKey] && !keysDown[vKey];
}

void KeyboardInput::PostUpdate()
{
	memcpy(m_previousKeysDown, keysDown, sizeof(bool) * InputHelpers::KEYS_ARRAY_LEN);
}

#pragma once
#include <Windows.h>
#include <XInput.h>
#include <string>

namespace InputHelpers
{
	const int KEYS_ARRAY_LEN = 256;     // size of key arrays

	const UCHAR KEYS_DOWN = 1;
	const UCHAR KEYS_PRESSED = 2;
	const UCHAR MOUSE = 4;
	const UCHAR TEXT_IN = 8;
	const UCHAR KEYS_MOUSE_TEXT = KEYS_DOWN + KEYS_PRESSED + MOUSE + TEXT_IN;
}

class KeyboardInput
{
private:
	static KeyboardInput* instance;

	bool keysDown[InputHelpers::KEYS_ARRAY_LEN];     // true if specified key is down

public:
	static KeyboardInput* GetInstance();

	void keyDown(WPARAM);
	void keyUp(WPARAM);

	bool isKeyDown(UCHAR) const;
	bool isKeyUp(UCHAR) const;

	LPCWSTR getKeyPressedString(UCHAR);
};


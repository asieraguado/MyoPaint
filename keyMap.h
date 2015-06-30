#pragma once

#include <string>
#include <map>
#include <vector>
#define WINVER 0x0500
#include <windows.h> // Necessary for key pressing
#include <windef.h>
#include <windowsx.h>
#include <tchar.h>
#include "SendKeys.h"

class keyMap {
public:
	static std::map<std::string, std::pair<byte, byte > > keys;
	// This structure will be used to create the keyboard input event.
	static INPUT ip;

	keyMap();

	inline void addKey(std::string key, byte code, byte hex);
	inline byte getCode(std::string key);
	inline byte getHex(std::string key);

	// KEYBOARD INPUT
	void pressKey(std::string key);
	void releaseKey(std::string key);

	// MOUSE INPUT
	void leftClick();
	void releaseLeftClick();
};
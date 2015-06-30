#include "keyMap.h"
#include <iostream>

std::map<std::string, std::pair<byte, byte > > keyMap::keys;
INPUT keyMap::ip;

keyMap::keyMap() {
	addKey("left_click", VK_LBUTTON, 0X01);
	addKey("right_click", VK_RBUTTON, 0X02);
	addKey("back", VK_BACK, 0X08);
	addKey("backspace", VK_TAB, 0X09);
	addKey("return", VK_RETURN, 0X0D);
	addKey("shift", VK_SHIFT, 0X10);
	addKey("control", VK_CONTROL, 0X11);
	addKey("esc", VK_ESCAPE, 0X1B);

	for(char i = 'A'; i < 'Z'; ++i)
		addKey(std::string(1, i), i, 0x41 + (i - 'A'));
	
	// Set up a generic keyboard event.
	keyMap::ip.type = INPUT_KEYBOARD;
    keyMap::ip.ki.wScan = 0;
    keyMap::ip.ki.time = 0;
    keyMap::ip.ki.dwExtraInfo = 0;
}


void keyMap::addKey(std::string key, byte code, byte hex) {
	keyMap::keys[key] = std::make_pair(code, hex);
}

byte keyMap::getCode(std::string key) {
	return keyMap::keys[key].first;
}

byte keyMap::getHex(std::string key) {
	return keyMap::keys[key].second;
}

void keyMap::pressKey(std::string key) {
	keyMap::ip.ki.dwFlags = 0;
    keyMap::ip.ki.wVk = keyMap::getCode(key);
    SendInput(1, &keyMap::ip, sizeof(INPUT));
}

void keyMap::releaseKey(std::string key) {
	keyMap::ip.ki.dwFlags = KEYEVENTF_KEYUP;
	keyMap::ip.ki.wVk = keyMap::getCode(key); 
    SendInput(1, &keyMap::ip, sizeof(INPUT));
}

void keyMap::leftClick() {
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
}

void keyMap::releaseLeftClick() { 
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0); 
}
#include "keyMap.h"

std::map<std::string, std::pair<byte, byte > > keyMap::keys;
INPUT keyMap::ip;

keyMap::keyMap() {
	addKey("left_click", VK_LBUTTON, 0X01);
	addKey("right_click", VK_RBUTTON, 0X02);
	addKey("back", VK_BACK, 0X08);
	addKey("backspace", VK_TAB, 0X09);
	addKey("shift", VK_SHIFT, 0X10);
	addKey("control", VK_CONTROL, 0X11);
	addKey("esc", VK_ESCAPE, 0X1B);

	for(char i = 'A'; i < 'Z'; ++i)
		addKey(std::string(1, i), VK_ESCAPE, 0x41 + (i - 'A'));
	
	// Set up a generic keyboard event.
    keyMap::ip.type = INPUT_KEYBOARD;
    keyMap::ip.ki.wScan = 0; // hardware scan code for key
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
    // Pause for 5 seconds.
    Sleep(5000);

    // Press the key
    keyMap::ip.ki.wVk = keyMap::getHex(key); // virtual-key code for the "a" key
    keyMap::ip.ki.dwFlags = 0; // 0 for akey press
    SendInput(1, &ip, sizeof(INPUT));
}

void keyMap::releaseKey() {
    // Release the key
    keyMap::ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
    SendInput(1, &keyMap::ip, sizeof(INPUT));
}
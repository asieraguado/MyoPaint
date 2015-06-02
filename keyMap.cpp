#include "keyMap.h"

keyMap::keyMap(void) {
	addKey("left_click", "VK_LBUTTON", "0X01");
	addKey("right_click", "VK_RBUTTON", "0X02");
	addKey("back", "VK_BACK", "0X08");
	addKey("backspace", "VK_TAB", "0X09");
	addKey("shift", "VK_SHIFT", "0X10");
	addKey("control", "VK_CONTROL", "0X11");
	addKey("esc", "VK_ESCAPE", "0X1B");

	// Numbers
	for(int i = 0; i < 10; ++i)
		addKey(std::to_string(i), "", "0X" + std::to_string(30 + i));
}

keyMap::~keyMap(void) {
}

void addKey(std::string key, std::string code, std::string hex) {
	keyMap::keys[key] = std::vector<std::string>(2, "");
	keyMap::keys[key][0] = code;
	keyMap::keys[key][1] = hex;
}

std::string getCode(std::string key) {
	return keyMap::keys[key][0];
}

std::string getHex(std::string key) {
	return keyMap::keys[key][1];
}
#pragma once

#include "keyMap.h"

class GIMPController {
private:
	keyMap *keymap;
public:
	GIMPController();

	// GIMP control
	void focusGIMP();
	void newCanvas();

	// Drawing options
	void action();
	void stopAction();

	// Tools options
	void selectPen();
	void selectBrush();
	void selectEraser();
};
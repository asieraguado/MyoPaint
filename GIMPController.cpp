#include "GIMPController.h"

GIMPController::GIMPController() {
	keymap = new keyMap();
}

void GIMPController::focusGIMP() {
	SetForegroundWindow(FindWindowA(NULL,"GimpProxy"));
}

void GIMPController::newCanvas() {
	keymap->pressKey("control");
	keymap->pressKey("N");
	keymap->releaseKey("N");
	keymap->releaseKey("control");
}

void GIMPController::action() {
	keymap->leftClick();
}

void GIMPController::stopAction() {
	keymap->releaseLeftClick();
}

void GIMPController::selectPen() {
	keymap->pressKey("N");
	keymap->releaseKey("N");
}

void GIMPController::selectBrush() {
	keymap->pressKey("P");
	keymap->releaseKey("P");
}

void GIMPController::selectEraser() {
	keymap->pressKey("shift");
	keymap->pressKey("E");
	keymap->releaseKey("E");
	keymap->releaseKey("shift");
}

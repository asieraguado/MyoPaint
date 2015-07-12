#include "histGUI.h"

void emgdatasampleVisualStudio2013::histGUI::updateHist(histogram h) {
	graphDrawingArea->Clear(this->BackColor);
	std::vector<histbar> bars = h.getData();
	int leftpos = lblLeft->Left;
	for (int i = 0; i < bars.size(); i++) {
		graphDrawingArea->FillRectangle(gcnew SolidBrush(Color::Red),
			leftpos,
			280 - bars[i].value*20, 40, bars[i].value*20);
		graphDrawingArea->DrawRectangle(gcnew Pen(Color::Black),
			leftpos,
			280 - bars[i].value*20, 40, bars[i].value*20);
		leftpos += 50;
	}
}
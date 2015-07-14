#include "histGUI.h"

void emgdatasampleVisualStudio2013::histGUI::updateHist(histogram h) {
	graphDrawingArea->Clear(this->BackColor);
	std::vector<histbar> bars = h.getData();
	int leftpos = lblLeft->Left;
	for (int i = 0; i < bars.size(); i++) {
		graphDrawingArea->FillRectangle(gcnew SolidBrush(Color::Red),
			leftpos,
			150 - bars[i].value*12, 40, bars[i].value*12);
		graphDrawingArea->DrawRectangle(gcnew Pen(Color::Black),
			leftpos,
			150 - bars[i].value*12, 40, bars[i].value*12);
		// Label under bar
		graphDrawingArea->DrawString(gcnew System::String(bars[i].gesture.c_str()), gcnew System::Drawing::Font("Tahoma", 11), gcnew SolidBrush(Color::Black), leftpos+5, 160);

		leftpos += 60;
	}
}
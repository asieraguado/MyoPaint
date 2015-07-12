#include "histogram.h"


histogram::histogram()
{
	data.clear();
	gestures.clear();
}

void histogram::restart() {
	for (int i = 0; i < data.size(); i++) {
		data[i].value = 0;
	}
}

void histogram::add_instant(std::string gesture) {
	int gnum;
	if (gestures.count(gesture) == 0) {
		gnum = data.size();
		gestures[gesture] = gnum;
		histbar newbar;
		newbar.gesture = gesture;
		newbar.value = 1;
		data.push_back(newbar);
	}
	else {
		gnum = gestures[gesture];
		data[gnum].value++;
	}
}

std::string histogram::peak()  {
	histbar max;
	max.gesture = "none";
	max.value = 0;
	for (int i = 0; i < data.size(); i++) {
		if (max.value < data[i].value)
			max = data[i];
	}
	return max.gesture;
}

std::vector<histbar> histogram::getData() {
	return data;
}
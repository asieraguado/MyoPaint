#pragma once
#include <vector>
#include <map>
#include <string>

typedef struct {
	std::string gesture;
	int value;
} histbar;

class histogram
{
public:
	histogram();
	void add_instant(std::string gesture);
	std::string peak();
	std::vector<histbar> getData();
	void restart();

private:
	std::map<std::string, int> gestures;
	std::vector<histbar> data;
};
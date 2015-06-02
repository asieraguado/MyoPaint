#pragma once

#include <string>
#include <map>
#include <vector>

class keyMap
{
public:
	keyMap(void);
	~keyMap(void);

	static std::map<std::string, std::vector<std::string> > keys;
};


#pragma once

#include <string>

class GameObject {
public:
	std::string id;
	std::string name;
	std::string shortname;
	std::string type;
	std::string path;
	GameObject();
	virtual ~GameObject();
};


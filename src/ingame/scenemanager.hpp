#pragma once

#include <string>

#include "../log/log.hpp"

class SceneManager {
	static Log* log;
public:
	SceneManager();
	virtual ~SceneManager();
	
	bool init();
	void nextScene(std::string const &id);
};


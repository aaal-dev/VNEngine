#pragma once

#include "../config/configmanager.hpp"
#include "../log/log.hpp"
#include "openal.hpp"

class AudioManager
{
	// Variables
	static Log*           log;
//	static ConfigManager* configManager;
//	Config*               config;
	
public:
	bool     init();
	         AudioManager();
	virtual ~AudioManager();

};


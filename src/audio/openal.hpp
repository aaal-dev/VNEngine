#pragma once

#include "AL/al.h"
#include "AL/alc.h"
#include "AL/alext.h"


#include "../config/configmanager.hpp"
#include "../log/log.hpp"

class OpenAl
{
	// Variables
	static Log*           log;
	//static ConfigManager* configManager;
	//Config*               config;
	
public:
	bool init();
	void stop();
	
	OpenAl();
	virtual ~OpenAl();
};


#pragma once

// GLFW
#include <GLFW/glfw3.h>

#include "../config/configmanager.hpp"
#include "../log/log.hpp"

class TimeManager
{
	// ----------------------------------------------------------- Variables -- 
	static TimeManager*  _instance;
	static Log*  log;
//	static ConfigManager*  configManager;
//	Config*  config;
	
	double   _currentTime;
	double   _deltaTime;
	double   _lastTime;
	int   _frames;
	
	// ----------------------------------------------------------- Functions -- 
	
	
public:
	// ----------------------------------------------------------- Functions -- 
	static TimeManager*  get();
	static void   release();
	
	bool   init();
	void   run();
	bool   update();
	
	double   currentTime();
	double   deltaTime();
	double   lastTime();
	
private:
	TimeManager();
	virtual  ~TimeManager();

};


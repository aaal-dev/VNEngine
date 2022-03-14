#pragma once

#include "log/log.hpp"

//#include "audio/audio.hpp"
#include "config/configmanager.hpp"
#include "ingame/gamemanager.hpp"
#include "render/render.hpp"
#include "render/rendermanager.hpp"
//#include "timemanager.hpp"
//#include "video/video.hpp"
#include "window/windowmanager.hpp"


class App {
public:
	// ---------------------------------------------------- public.functions -- 
	bool init();
	void run();
	void stop();
	
	
private:
	// --------------------------------------------------- private.variables -- 
	static Log *log;
	acb::Section *config {nullptr};
	
	ConfigManager configManager;
	ControlManager controlManager;
	GameManager gameManager;
	WindowManager windowManager;
	Render render;
	RenderManager renderManager;
	
//	TimeManager timeManager;
//	AudioManager audioManager;
	
	
	bool active {false};
	
	// --------------------------------------------------- private.functions -- 
	void update();
	void proceed();
	
	
public:
	App();
	~App();
};

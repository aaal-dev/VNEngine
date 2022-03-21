#pragma once

//#include "audio/audio.hpp"
#include "config/configmanager.hpp"
#include "ingame/gamemanager.hpp"
#include "log/log.hpp"
#include "render/render.hpp"
#include "render/rendermanager.hpp"
//#include "time/timemanager.hpp"
//#include "video/video.hpp"
#include "window/windowmanager.hpp"

/**
 * @class App
 * @author aaal
 * @date 19/03/22
 * @file app.hpp
 * @brief
 */
class App {
	enum {
		APP_FAIL,
		APP_OK
	};
public:
// -------------------------------------------------------- public.variables --
// -------------------------------------------------------- public.functions --
	/**
	 * @brief Initional configuration of application
	 * @return OK or fail
	 */
	bool  init();

	/**
	 * @brief Runs the application
	 */
	void  run();

	/**
	 * @brief Executes requered methods for cleaning purpose
	 */
	void  stop();

private:
// ------------------------------------------------------- private.variables --

	static Log  *log;
	acb::Section  *config {nullptr};

	ConfigManager  configManager;
	ControlManager  controlManager;
	GameManager  gameManager;
	WindowManager  windowManager;
	RenderManager  renderManager;

//	TimeManager  timeManager;
//	AudioManager  audioManager;


	bool  active {false};

// ------------------------------------------------------- private.functions --

	void  update();
	void  proceed();

public:
	App();
	virtual ~App();
};

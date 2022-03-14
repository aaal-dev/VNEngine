#pragma once

#include <map>
#include <vector>

// GLFW
#include <GLFW/glfw3.h>

// Inner classes
#include "../log/log.hpp"
#include "../config/configmanager.hpp"
#include "../control/controlmanager.hpp"

#include "monitor.hpp"
#include "window.hpp"

class WindowManager {
public:
	// ---------------------------------------------------- public.variables -- 
	int monitorsCount;
	Monitor **avalableMonitors;
	Monitor *primaryMonitor;
	
	// ---------------------------------------------------- public.functions -- 
	bool init();
	bool update();
	void terminate();
	bool createWindow();
	void makeActive(GLFWwindow* window);
	void cleanup();
	
	// Callback functions
	static void framebufferSizeCallback
	(GLFWwindow *window, int width, int height);
	
	
private:
	// --------------------------------------------------- private.variables -- 
	static Log *log;
	acb::Section *config {nullptr};
//	static ConfigManager *configManager;
	static ControlManager *controlManager;
	
	unsigned int activeWindowIndx;
	GLFWwindow *activeWindow;
	Window window;

	
	// --------------------------------------------------- private.functions -- 
	float getFPS();
	void updateTitle(GLFWwindow *window);
	bool getMonitors();
	bool getPrimaryMonitor();
	
	// Callback functions
	static void glfwErrorCallback(int error, const char* description);
	
	
public:
	         WindowManager();
	virtual ~WindowManager();
};

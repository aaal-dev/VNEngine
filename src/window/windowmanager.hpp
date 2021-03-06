#pragma once

#include <map>
#include <memory>
#include <vector>

#include <GLFW/glfw3.h>

#include "../log/log.hpp"
#include "../config/configmanager.hpp"

#include "monitor.hpp"
#include "window.hpp"

class WindowManager {
public:
// -------------------------------------------------------- public.variables --

	int monitorsCount;
	Monitor **avalableMonitors;
	Monitor *primaryMonitor;
	
// -------------------------------------------------------- public.functions --

	bool init();
	bool update();
	void terminate();
	bool createWindow();
	void makeActive(GLFWwindow* window);
	Window* getActive();
	void cleanup();
	
	// Callback functions
	static void framebufferSizeCallback
	(GLFWwindow *window, int width, int height);
	
private:
// ------------------------------------------------------- private.variables --

	static Log *log;
	acb::Section *config {nullptr};
	
	unsigned int activeWindowIndx;
	GLFWwindow *activeWindow;
	Window _window;
	
// ------------------------------------------------------- private.functions --

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

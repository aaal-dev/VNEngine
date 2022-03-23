#pragma once

#include <string>

#include <GLFW/glfw3.h>

#include "../actions/closewindow.hpp"
#include "../control/controlmanager.hpp"
#include "../event/eventmanager.hpp"
#include "../event/event.hpp"
#include "../event/eventcallback.hpp"

#include "iwindow.hpp"

class Window : public IWindow {
public:
	std::string title;
	int width,  minWidth {640};
	int height, minHeight {480};
	
	void create();
	void destroy();
	
	void close();
	bool update();
	
	void updateTitle(std::string const &text);
	
	bool exist();
	void makeActive();
	void swapInterval(int interval);
	
	void setKeyCallback(); //GLFWkeyfun callbackFunction);
//	void setKeyCharCallback(GLFWcharfun callbackFunction);
//	void keyboardCharacterModifiersCallback(GLFWcharmodsfun callbackFunction);
//	void mouseButtonCallback(GLFWmousebuttonfun callbackFunction);
//	void mousePositionCallback(GLFWcursorposfun callbackFunction);
//	void mouseEnterCallback(GLFWcursorenterfun callbackFunction);
//	void mouseScrollCallback(GLFWscrollfun callbackFunction);
//	void dropCallback(GLFWdropfun callbackFunction);
//	void windowPositionCallback(GLFWwindowposfun callbackFunction);
//	void windowSizeCallback(GLFWwindowsizefun callbackFunction);
//	void windowCloseCallback(GLFWwindowclosefun callbackFunction);
//	void windowRefreshCallback(GLFWwindowrefreshfun callbackFunction);
//	void windowFocusCallback(GLFWwindowfocusfun callbackFunction);
//	void windowIconifyCallback(GLFWwindowiconifyfun callbackFunction);
//	void windowMaximizeCallback(GLFWwindowmaximizefun callbackFunction);
//	void framebufferSizeCallback(GLFWframebuffersizefun callbackFunction);
//	void windowContentScaleCallback(GLFWwindowcontentscalefun callbackFunction);
//	
private:
	GLFWwindow *window {nullptr};
	ControlManager controlManager;
	EventManager eventManager;
	actions::CloseWindow closeWindowAction;
};

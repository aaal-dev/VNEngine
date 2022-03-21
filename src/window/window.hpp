#pragma once

#include <string>

#include <GLFW/glfw3.h>

class Window {
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
	
	void keyboardCallback(GLFWkeyfun callbackFunction);
	void keyboardCharacterCallback(GLFWcharfun callbackFunction);
	void keyboardCharacterModifiersCallback(GLFWcharmodsfun callbackFunction);
	void mouseButtonCallback(GLFWmousebuttonfun callbackFunction);
	void mousePositionCallback(GLFWcursorposfun callbackFunction);
	void mouseEnterCallback(GLFWcursorenterfun callbackFunction);
	void mouseScrollCallback(GLFWscrollfun callbackFunction);
	void dropCallback(GLFWdropfun callbackFunction);
	void windowPositionCallback(GLFWwindowposfun callbackFunction);
	void windowSizeCallback(GLFWwindowsizefun callbackFunction);
	void windowCloseCallback(GLFWwindowclosefun callbackFunction);
	void windowRefreshCallback(GLFWwindowrefreshfun callbackFunction);
	void windowFocusCallback(GLFWwindowfocusfun callbackFunction);
	void windowIconifyCallback(GLFWwindowiconifyfun callbackFunction);
	void windowMaximizeCallback(GLFWwindowmaximizefun callbackFunction);
	void framebufferSizeCallback(GLFWframebuffersizefun callbackFunction);
	void windowContentScaleCallback(GLFWwindowcontentscalefun callbackFunction);
	
private:
	GLFWwindow *window;
};

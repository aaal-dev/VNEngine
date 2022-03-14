#pragma once

#include <string>

class Window {
	GLFWwindow *window;
public:
	std::string title;
	int width,  minWidth {640};
	int height, minHeight {480};
	
	void create() { 
		window = glfwCreateWindow(width, height, title.data(), NULL, NULL); 
		glfwSetWindowSizeLimits(window, minWidth, minHeight, GLFW_DONT_CARE, GLFW_DONT_CARE);
	}
	void close() { glfwSetWindowShouldClose(window, GL_TRUE); }
	void destroy() { glfwDestroyWindow(window); }
	
	bool update() {
		glfwSwapBuffers(window);
		return !glfwWindowShouldClose(window);
	}
	
	void updateTitle(std::string const &text) {
		std::string newTitle = title + " " + text;
		glfwSetWindowTitle(window, newTitle.data());
	}
	
	bool exist() { return (bool)window; }
	void makeActive() { glfwMakeContextCurrent(window); }
	void swapInterval(int interval) { glfwSwapInterval(interval); }
	
	void keyboardCallback(GLFWkeyfun callbackFunction) {
		glfwSetKeyCallback(window, callbackFunction);
	}
	
	void keyboardCharacterCallback(GLFWcharfun callbackFunction) {
		glfwSetCharCallback(window, callbackFunction);
	}
	
	void keyboardCharacterModifiersCallback(GLFWcharmodsfun callbackFunction) {
		glfwSetCharModsCallback(window, callbackFunction);
	}
	
	void mouseButtonCallback(GLFWmousebuttonfun callbackFunction) {
		glfwSetMouseButtonCallback(window, callbackFunction);
	}
	
	void mousePositionCallback(GLFWcursorposfun callbackFunction) {
		glfwSetCursorPosCallback(window, callbackFunction);
	}
	
	void mouseEnterCallback(GLFWcursorenterfun callbackFunction) {
		glfwSetCursorEnterCallback(window, callbackFunction);
	}
	
	void mouseScrollCallback(GLFWscrollfun callbackFunction) {
		glfwSetScrollCallback(window, callbackFunction); 
	}
	
	void dropCallback(GLFWdropfun callbackFunction) {
		glfwSetDropCallback(window, callbackFunction);
	}
	
	void windowPositionCallback(GLFWwindowposfun callbackFunction) {
		glfwSetWindowPosCallback(window, callbackFunction);
	}
	
	void windowSizeCallback(GLFWwindowsizefun callbackFunction) {
		glfwSetWindowSizeCallback(window, callbackFunction);
	}
	
	void windowCloseCallback(GLFWwindowclosefun callbackFunction) {
		glfwSetWindowCloseCallback(window, callbackFunction);
	}
	
	void windowRefreshCallback(GLFWwindowrefreshfun callbackFunction) {
		glfwSetWindowRefreshCallback(window, callbackFunction);
	}
	
	void windowFocusCallback(GLFWwindowfocusfun callbackFunction) {
		glfwSetWindowFocusCallback(window, callbackFunction);
	}
	
	void windowIconifyCallback(GLFWwindowiconifyfun callbackFunction) {
		glfwSetWindowIconifyCallback(window, callbackFunction);
	}
	
	void windowMaximizeCallback(GLFWwindowmaximizefun callbackFunction) {
		glfwSetWindowMaximizeCallback(window, callbackFunction);
	}
	
	void framebufferSizeCallback(GLFWframebuffersizefun callbackFunction) {
		glfwSetFramebufferSizeCallback(window, callbackFunction);
	}
	
	void windowContentScaleCallback(GLFWwindowcontentscalefun callbackFunction) {
		glfwSetWindowContentScaleCallback(window, callbackFunction);
	}
	
};

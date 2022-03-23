#include "window.hpp"

void Window::create() {
	window = glfwCreateWindow(width, height, title.data(), NULL, NULL);
	glfwSetWindowUserPointer(window, this);
	glfwSetWindowSizeLimits(window, minWidth, minHeight, GLFW_DONT_CARE, GLFW_DONT_CARE);
}

void Window::close() {
	glfwSetWindowShouldClose(window, GL_TRUE);
}

void Window::destroy() {
	glfwDestroyWindow(window);
}

bool Window::update() {
	glfwSwapBuffers(window);
	return !glfwWindowShouldClose(window);
}

void Window::updateTitle(std::string const& text) {
	std::string newTitle = title + " " + text;
	glfwSetWindowTitle(window, newTitle.data());
}

bool Window::exist() {
	return (bool)window;
}

void Window::makeActive() {
	glfwMakeContextCurrent(window);
	
	auto callback = std::make_unique<EventCallback<Window>>(this, &Window::close);
	auto event = std::make_unique<Event>();
	event->addCallback(std::move(callback));
	eventManager.addEvent("close_window", std::move(event));
	
	setKeyCallback();
}

void Window::swapInterval(int interval) {
	glfwSwapInterval(interval);
}

void Window::setKeyCallback() {
	auto keyCallback = 
		[]
		(GLFWwindow* window, int key, int scancode, int action, int mode) 
		{
			auto& ptr = *(Window*)glfwGetWindowUserPointer(window);
			ptr.controlManager.keyboard.keyPressed(key, scancode, action, mode);
			ptr.eventManager.execEvent("close_window");
		};
	glfwSetKeyCallback(window, keyCallback);
}

//void Window::mouseButtonCallback(GLFWmousebuttonfun callbackFunction) {
//	glfwSetMouseButtonCallback(window, callbackFunction);
//}
//
//void Window::mousePositionCallback(GLFWcursorposfun callbackFunction) {
//	glfwSetCursorPosCallback(window, callbackFunction);
//}
//
//void Window::mouseEnterCallback(GLFWcursorenterfun callbackFunction) {
//	glfwSetCursorEnterCallback(window, callbackFunction);
//}
//
//void Window::mouseScrollCallback(GLFWscrollfun callbackFunction) {
//	glfwSetScrollCallback(window, callbackFunction);
//}
//
//void Window::dropCallback(GLFWdropfun callbackFunction) {
//	glfwSetDropCallback(window, callbackFunction);
//}
//
//void Window::windowPositionCallback(GLFWwindowposfun callbackFunction) {
//	glfwSetWindowPosCallback(window, callbackFunction);
//}
//
//void Window::windowSizeCallback(GLFWwindowsizefun callbackFunction) {
//	glfwSetWindowSizeCallback(window, callbackFunction);
//}
//
//void Window::windowCloseCallback(GLFWwindowclosefun callbackFunction) {
//	glfwSetWindowCloseCallback(window, callbackFunction);
//}
//
//void Window::windowRefreshCallback(GLFWwindowrefreshfun callbackFunction) {
//	glfwSetWindowRefreshCallback(window, callbackFunction);
//}
//
//void Window::windowFocusCallback(GLFWwindowfocusfun callbackFunction) {
//	glfwSetWindowFocusCallback(window, callbackFunction);
//}
//
//void Window::windowIconifyCallback(GLFWwindowiconifyfun callbackFunction) {
//	glfwSetWindowIconifyCallback(window, callbackFunction);
//}
//
//void Window::windowMaximizeCallback(GLFWwindowmaximizefun callbackFunction) {
//	glfwSetWindowMaximizeCallback(window, callbackFunction);
//}
//
//void Window::framebufferSizeCallback(GLFWframebuffersizefun callbackFunction) {
//	glfwSetFramebufferSizeCallback(window, callbackFunction);
//}
//
//void Window::windowContentScaleCallback(GLFWwindowcontentscalefun callbackFunction) {
//	glfwSetWindowContentScaleCallback(window, callbackFunction);
//}

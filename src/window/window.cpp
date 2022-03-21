#include "window.hpp"

void Window::create() {
	window = glfwCreateWindow(width, height, title.data(), NULL, NULL);
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
}
void Window::swapInterval(int interval) {
	glfwSwapInterval(interval);
}

void Window::keyboardCallback(GLFWkeyfun callbackFunction) {
	glfwSetKeyCallback(window, callbackFunction);
}

void Window::keyboardCharacterCallback(GLFWcharfun callbackFunction) {
	glfwSetCharCallback(window, callbackFunction);
}

void Window::keyboardCharacterModifiersCallback(GLFWcharmodsfun callbackFunction) {
	glfwSetCharModsCallback(window, callbackFunction);
}

void Window::mouseButtonCallback(GLFWmousebuttonfun callbackFunction) {
	glfwSetMouseButtonCallback(window, callbackFunction);
}

void Window::mousePositionCallback(GLFWcursorposfun callbackFunction) {
	glfwSetCursorPosCallback(window, callbackFunction);
}

void Window::mouseEnterCallback(GLFWcursorenterfun callbackFunction) {
	glfwSetCursorEnterCallback(window, callbackFunction);
}

void Window::mouseScrollCallback(GLFWscrollfun callbackFunction) {
	glfwSetScrollCallback(window, callbackFunction);
}

void Window::dropCallback(GLFWdropfun callbackFunction) {
	glfwSetDropCallback(window, callbackFunction);
}

void Window::windowPositionCallback(GLFWwindowposfun callbackFunction) {
	glfwSetWindowPosCallback(window, callbackFunction);
}

void Window::windowSizeCallback(GLFWwindowsizefun callbackFunction) {
	glfwSetWindowSizeCallback(window, callbackFunction);
}

void Window::windowCloseCallback(GLFWwindowclosefun callbackFunction) {
	glfwSetWindowCloseCallback(window, callbackFunction);
}

void Window::windowRefreshCallback(GLFWwindowrefreshfun callbackFunction) {
	glfwSetWindowRefreshCallback(window, callbackFunction);
}

void Window::windowFocusCallback(GLFWwindowfocusfun callbackFunction) {
	glfwSetWindowFocusCallback(window, callbackFunction);
}

void Window::windowIconifyCallback(GLFWwindowiconifyfun callbackFunction) {
	glfwSetWindowIconifyCallback(window, callbackFunction);
}

void Window::windowMaximizeCallback(GLFWwindowmaximizefun callbackFunction) {
	glfwSetWindowMaximizeCallback(window, callbackFunction);
}

void Window::framebufferSizeCallback(GLFWframebuffersizefun callbackFunction) {
	glfwSetFramebufferSizeCallback(window, callbackFunction);
}

void Window::windowContentScaleCallback(GLFWwindowcontentscalefun callbackFunction) {
	glfwSetWindowContentScaleCallback(window, callbackFunction);
}

#include "keyboard.hpp"

void Keyboard::keyPressed (int key, int scancode, int action, int mode) {
	if (action == GLFW_PRESS) {
		this->key[key] = true;
	} else if (action == GLFW_RELEASE) {
		this->key[key] = false;
	}
}

void Keyboard::keyboardCallback
(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE)
		glfwSetWindowShouldClose(window, GL_TRUE);
//	_instance->keyPressed(key, scancode, action, mode);
}

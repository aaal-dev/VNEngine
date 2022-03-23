#include "mouse.hpp"


void cob::Mouse::update() {
	offsetx = x - lastx;
	offsety = lasty - y;
	lastx = x;
	lasty = y;
	offset *= sensitivity;
}

void cob::Mouse::buttonPressed(int button, int action, int modifiers) {
	if(action == GLFW_PRESS) {
		this->button[button] = true;
		
		switch(button) {
		case GLFW_MOUSE_BUTTON_LEFT:
			break;
			
		case GLFW_MOUSE_BUTTON_MIDDLE:
			break;
			
		case GLFW_MOUSE_BUTTON_RIGHT:
			break;
		}
		
	} else if(action == GLFW_RELEASE) {
		this->button[button] = false;
		
		switch(button) {
		case GLFW_MOUSE_BUTTON_LEFT:
			break;
			
		case GLFW_MOUSE_BUTTON_MIDDLE:
			break;
			
		case GLFW_MOUSE_BUTTON_RIGHT:
			break;
		}
	}
}

void cob::Mouse::moveTo(float x, float y) {
	this->x = x;
	this->y = y;
//	screenx = (2.0f * x) / screen.w - 1.0f;
//	screeny = 1.0f - (2.0f * y) / screen.h;
}

void cob::Mouse::scrolled(float x, float y) {
	scrollx -= x;
	scrolly -= y;
	
	if(scrolly < 1.0f)
		scrolly = 1.0f;
		
	if(scrolly > 45.0f)
		scrolly = 45.0f;
}

void cob::Mouse::buttonCallback(GLFWwindow* window, int button, int action, int modifiers) {
	(void)window;
//  _instance->mouseButtonPressed(button, action, modifiers);
}
void cob::Mouse::positionCallback(GLFWwindow* window, double x, double y) {
	(void)window;
//  _instance->mousePosition(x, y);
}
void cob::Mouse::scrollCallback(GLFWwindow* window, double x, double y) {
	(void)window;
//  _instance->mouseScrolled(x, y);
}

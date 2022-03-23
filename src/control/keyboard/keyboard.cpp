#include "keyboard.hpp"

cob::Keyboard::Keyboard() {
	
}

cob::Keyboard::~Keyboard() {}

void cob::Keyboard::keyPressed(int key, int scancode, int action, int mode) {
	if(action == GLFW_PRESS && key == GLFW_KEY_UNKNOWN) {
		this->unknownKey.press();
	} else if(action == GLFW_PRESS) {
		this->key[key].press();
		
	} else if(action == GLFW_RELEASE) {
		this->key[key].release();
	}
}

void cob::Keyboard::setKeyAction(int key, actions::IAction *action) {
	this->key[key].setAction(action);
}

//void cob::Keyboard::keyCallback
//(GLFWwindow* window, int key, int scancode, int action, int mode) {
//	auto ptr = (Window*)glfwGetWindowUserPointer(window);
//	ptr->controlManager.keyboard.keyPressed(key, scancode, action, mode);
//}



//void cob::Keyboard::keyboardCharacterCallback(GLFWcharfun callbackFunction) {
//	glfwSetCharCallback(window, callbackFunction);
//}
//
//void cob::Keyboard::keyboardCharacterModifiersCallback(GLFWcharmodsfun callbackFunction) {
//	glfwSetCharModsCallback(window, callbackFunction);
//}

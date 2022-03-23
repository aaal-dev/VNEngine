#pragma once

#include <GLFW/glfw3.h>

#include "key.hpp"

namespace cob {

class Keyboard {
public:
	Key key[GLFW_KEY_LAST];
	Key unknownKey;
	
	void keyPressed(int key, int scancode, int action, int mode);
	void setKeyAction(int key, actions::IAction *action);
	
	static void keyCallback
	(GLFWwindow *window, int key, int scancode, int action, int mode);
	
	Keyboard();
	virtual ~Keyboard();
};

}
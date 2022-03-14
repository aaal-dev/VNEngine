#pragma once

// GLFW
#include <GLFW/glfw3.h>

struct Monitor {
	GLFWmonitor* monitor;
	const char* name;
	bool isPrimary;
	int videoModesCount;
	const GLFWvidmode* videoModes;
	const GLFWvidmode* curentVideoMode;
};

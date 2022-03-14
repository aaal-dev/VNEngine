#pragma once

// GLFW
#include <GLFW/glfw3.h>

#include "../config/configmanager.hpp"
#include "../log/log.hpp"
#include "../maths/maths.hpp"

#include "keyboard.hpp"
#include "mouse.hpp"




struct Screen {
	unsigned int w = 0, h = 0;
	float aspectRatio = 0.0f;
	
	void update() { aspectRatio = (float)w / (float)h; };
	
	Screen() {};
	Screen(int w, int h) : w(w), h(h) {};
	Screen(vec2 size) : w((unsigned int)size.w), h((unsigned int)size.h) {};
};



class ControlManager
{
public:
	enum class  Movement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,
		UP,
		DOWN
	};
	// ---------------------------------------------------- public.variables --
	Keyboard  keyboard;
	Mouse  mouse;
	Screen  screen;
	
	// ---------------------------------------------------- public.functions --
	void  update();
	void  screenSize(int w, int h);
	
	
private:
	// --------------------------------------------------- private.variables --
	static Log  *log;
	acb::Section *config {nullptr};
	
	
public:
	ControlManager();
	virtual  ~ControlManager();
};


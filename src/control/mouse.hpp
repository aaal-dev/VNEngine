#pragma once 

// GLFW
#include <GLFW/glfw3.h>

// Inner classes
#include "../maths/maths.hpp"

struct Mouse {
	// ---------------------------------------------------- public.variables --
	union {
		struct {
			float x = 0.0f;
			float y = 0.0f;
		};
		vec2 position;
	};
	union {
		struct {
			float screenx = 0.0f;
			float screeny = 0.0f;
		};
		vec2 screenPosition;
	};
	union {
		struct {
			float lastx = 512.0f;
			float lasty = 384.0f;
		};
		vec2 lastPosition;
	};
	union {
		struct {
			float offsetx = 0.0f;
			float offsety = 0.0f;
		};
		vec2 offset;
	};
	union {
		struct {
			float scrollx = 0.0f;
			float scrolly = 0.0f;
		};
		vec2 scroll;
	};
	
	float sensitivity = 0.1f;
	bool button[16] = {false};

	// ----------------------------------------------------- public.funtions --
	void update();
	void moveTo(float x, float y);
	void buttonPressed(int button, int action, int modifiers);
	void scrolled(float x, float y);

	static void positionCallback(GLFWwindow *window, double x, double y);
	static void buttonCallback
	(GLFWwindow *window, int button,int action, int modifiers);
	static void scrollCallback(GLFWwindow *window, double x, double y);


	Mouse() {};
	Mouse(int x, int y) : x(x), y(y) {};
	Mouse(vec2 pos) : x(pos.x), y(pos.y) {};
};

#include "controlmanager.hpp"

Log* ControlManager::log = nullptr;
cob::Keyboard ControlManager::keyboard;
cob::Mouse ControlManager::mouse;

// ---------------------------------------------------------- ControlManager --

ControlManager::ControlManager() {
	log = Log::get();
}

ControlManager::~ControlManager() {}

// --------------------------------------------------- public.ControlManager --

bool ControlManager::init() {
	auto keyEscapeAction = 
		[]
		()
		{EventManager eventManager;
		eventManager.execEvent("close_window");};
	auto action = new actions::Action(keyEscapeAction);
	keyboard.setKeyAction(GLFW_KEY_ESCAPE, action);
	return true;
}

void ControlManager::update() {
	mouse.update();
}

void ControlManager::screenSize(int w, int h) {
	screen.w = w;
	screen.h = h;
	screen.update();
}

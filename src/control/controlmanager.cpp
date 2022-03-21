#include "controlmanager.hpp"

Log* ControlManager::log = nullptr;

// ---------------------------------------------------------- ControlManager --

ControlManager::ControlManager() {
	log = Log::get();
}

ControlManager::~ControlManager() {}

// --------------------------------------------------- public.ControlManager --

void ControlManager::update() {
	mouse.update();
}

void ControlManager::screenSize(int w, int h) {
	screen.w = w;
	screen.h = h;
	screen.update();
}

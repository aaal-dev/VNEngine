#include "app.hpp"

Log* App::log = nullptr;

// --------------------------------------------------------------------- App --

App::App() {
	log = Log::get();
}

App::~App() {
	if(active) stop();
}

// -------------------------------------------------------------- public.App --

bool App::init() {
	// Logger
	if(!log->init()) return false;

	log->info("Appication initializing...");

	// Configurator
	if(!configManager.init()) return false;  // На всякий случай оставлю

	config = configManager.createSection("App");
	config->addProperty<std::string>("configFilePath", "app.ini");

	// In game management
	if(!gameManager.init()) return false;

	// Window management
	if(!windowManager.init()) return false;

	windowManager.createWindow();

	if(!renderManager.init()) return false;

//	if (!audioManager.init()) return false;

	// Collect settings from config file
	auto filepath = config->getValue<std::string>("configFilePath");
	configManager.readTOMLFile(filepath);

	active = true;
	log->done("Appication initialized");
	return true;
}

void App::run() {
	while(active) {
		update();
		proceed();
	}
}

void App::stop() {
	active = false;
//	timeManager->release();
//	controlManager->release();
	log->release();
}

// ------------------------------------------------------------- private.App --

void App::update() {
	controlManager.update();
//	timeManager->update();
	renderManager.update();
	active = windowManager.update();

}

void App::proceed() {
	renderManager.draw();
}

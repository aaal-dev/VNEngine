#include "audio.hpp"

Log* AudioManager::log = nullptr;
//ConfigManager* AudioManager::configManager = nullptr;

//// ==== AudioManager ==================================================== ////

AudioManager::AudioManager () {
	log = Log::get();
//	configManager = ConfigManager::get();
//	config = configManager->createConfig("Audio");
}
AudioManager::~AudioManager () {}

//// ==== AudioManager ==================================================== ////

bool AudioManager::init () {
	log->begin("Audio manager initializing...");
	OpenAl openAl;
	if (!openAl.init()) {
		log->error("Failed to initialize audio manager context.");
		return false;
	}
	log->done("Audio manager initialized");
	return true;
}

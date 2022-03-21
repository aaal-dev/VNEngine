#include "audio.hpp"

Log* AudioManager::log = nullptr;

// ------------------------------------------------------------ AudioManager --
AudioManager::AudioManager() {
	log = Log::get();
}
AudioManager::~AudioManager() {}

// ----------------------------------------------------- public.AudioManager --

bool AudioManager::init() {
	log->begin("Audio manager initializing...");
	OpenAl openAl;

	if(!openAl.init()) {
		log->error("Failed to initialize audio manager context.");
		return false;
	}

	log->done("Audio manager initialized");
	return true;
}

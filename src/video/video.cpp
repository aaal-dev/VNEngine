#include "video.hpp"

Log* VideoManager::log = nullptr;
//ConfigManager* VideoManager::configManager = nullptr;

//// ==== VideoManager ==================================================== ////

VideoManager::VideoManager () {
	log = Log::get();
//	configManager = ConfigManager::get();
//	config = configManager->createConfig("Video");
}

VideoManager::~VideoManager () {}

//// ==== VideoManager ==================================================== ////


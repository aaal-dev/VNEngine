#include "scenemanager.hpp"

Log* SceneManager::log = nullptr;

// ------------------------------------------------------------ SceneManager -- 

SceneManager::SceneManager () {
	log = Log::get();
}

SceneManager::~SceneManager(){}

// ----------------------------------------------------- public:SceneManager -- 

bool SceneManager::init () {
	log->info("initialize game manager start...");
	
	
	
	log->info("initialize game manager done!");
	return true;
}

void SceneManager::nextScene (std::string const &id) {
	
}

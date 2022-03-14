#include "configmanager.hpp"

Log* ConfigManager::log = nullptr;
acb::Config ConfigManager::appConfig;

// ----------------------------------------------------------- ConfigManager -- 

ConfigManager::ConfigManager () {
	log = Log::get();
}

ConfigManager::~ConfigManager () {}

// ---------------------------------------------------- public.ConfigManager -- 

bool ConfigManager::init () {
	log->info("initialize config manager start...");
	
	
	log->info("initialize config manager done!");
	return true;
}

acb::Section* ConfigManager::createSection (std::string const &name) {
	return appConfig.createSection(name);
}

acb::Section* ConfigManager::findSection (std::string const &name) {
	return appConfig.find(name);
}

void ConfigManager::readTOMLFile (std::string const &filepath) {
	ParserManager* manager = new ParserManager;
	TOMLTree* tree = manager->parseTOMLFile(filepath);
	if (tree->empty()) {
		log->warn("No configuration found in file %s", filepath.data());
	} else {
		appConfig.fill(tree);
	}
	delete tree;
	delete manager;
}




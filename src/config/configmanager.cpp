#include "configmanager.hpp"

Log* ConfigManager::log = nullptr;
acb::Config ConfigManager::appConfig{};

// ----------------------------------------------------------- ConfigManager --

ConfigManager::ConfigManager() {
	log = Log::get();
}

ConfigManager::~ConfigManager() {}

// ---------------------------------------------------- public.ConfigManager --

bool ConfigManager::init() {
	log->info("initialize config manager start...");
	
	
	log->info("initialize config manager done!");
	return true;
}

acb::Section* ConfigManager::createSection(std::string const &name)
	{return appConfig.create(name);}

acb::Section* ConfigManager::findSection(std::string const &name) 
	{return appConfig.find(name);}

void ConfigManager::readTOMLFile(std::string const &filepath) {
	auto manager = std::make_unique<ParserManager>();
	auto tree = manager->parseTOMLFile(filepath);
	
	if(tree->empty())
		log->warn("No configuration found in file %s", filepath.data());
	else
		appConfig.fill(tree.get());
}

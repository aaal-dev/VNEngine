#pragma once

#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <algorithm>

#include "../log/log.hpp"
#include "../parser/parsermanager.hpp"
#include "../utils/text.hpp"

#include "config.hpp"

/***
 * ConfigManager class is to work with app settings
 * - read settings from a TOML file
 * - read settings from a YAML file <- TODO(1)
 * - get settings from args passed through command line <- TODO
 * - collect setting from whole application
 * - save settings into a TOML or YAML file <- TODO(2)
 * */

class ConfigManager {
	using index = std::map<std::string, uint>;
	
public:
	static acb::Config appConfig;
	
	// ---------------------------------------------------- public.Functions -- 
	bool init();

	acb::Section* createSection(std::string const &name);
	acb::Section* findSection(std::string const &name);
	
	void readTOMLFile(std::string const &filepath);
	// TODO(1) void readYAMLFile(std::string const &filepath);
	// TODO(2) void writeToFile(std::string const &filepath);
	
private: 
	// --------------------------------------------------- private.Variables -- 
	static Log* log;
	
	
public:
	ConfigManager();
	~ConfigManager();
};

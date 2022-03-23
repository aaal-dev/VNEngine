#pragma once

#include <string>
#include <memory>

#include "../log/log.hpp"
#include "../parser/parsermanager.hpp"
#include "../utils/textutils.hpp"

#include "config.hpp"

/**
 * @class ConfigManager
 * @author drumbox
 * @date 18/03/22
 * @file configmanager.hpp
 * @brief Work with app's settings
 *
 * Creates section of properties and collect them in acb::Config object.
 * Gets settings data from a configuration files and fills existing sections
 * with parsed data.
 *
 * @todo Read settings from a YAML file
 * @todo Parse settings from args passed through command line
 * @todo Save settings into a TOML or YAML file
 */

class ConfigManager {

public:
// -------------------------------------------------------- public.variablse --
	
	static acb::Config appConfig;
	
// -------------------------------------------------------- public.functions --
	/**
	 * @brief Initional configuration of manager itself
	 * @return Ok or not
	 */
	bool init();
	
	/**
	 * @brief Creates a new section of properties
	 * @param name Name of a section that needs to create
	 * @return Pointer to a new section data
	 */
	acb::Section* createSection(std::string const &name);
	
	/**
	 * @brief Finds a existing section of properties
	 * @param name Name of a section that needs to find
	 * @return Pointer to a found section data or nullptr
	 */
	acb::Section* findSection(std::string const &name);
	
	/**
	 * @brief Parses a data from TOML configuration file to existing sections
	 * @param filepath Path to TOML configuration file
	 */
	void readTOMLFile(std::string const &filepath);
	
private:
// ------------------------------------------------------- private.variables --
	static Log* log;
	
public:
	ConfigManager();
	~ConfigManager();
};

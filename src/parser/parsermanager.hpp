#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <memory>
#include <vector>

#include "../log/log.hpp"

#include "node.hpp"
#include "iparser.hpp"
#include "tomlparser.hpp"
#include "yamlparser.hpp"

/**
 * @class ParserManager
 * @author drumbox
 * @date 19/03/22
 * @file parsermanager.hpp
 * @brief Work with different kind of parsers 
 */
class ParserManager {
public:
// -------------------------------------------------------- public.variables -- 
// -------------------------------------------------------- public.functions -- 
	/**
	 * @brief Initional configuration of manager itself
	 * @return Ok or not
	 */
	bool  init();
	
	/**
	 * @brief 
	 * @param filepath
	 * @return 
	 */
	std::unique_ptr<TOMLTree>  parseTOMLFile(std::string const &filepath);
	
	/**
	 * @brief 
	 * @param filepath
	 * @return 
	 */
	std::unique_ptr<YAMLTree>  parseYAMLFile(std::string const &filepath);
	
	/**
	 * @brief 
	 * @param filepath
	 * @return 
	 */
	std::string  readShaderFile(std::string const &filepath);
	
private:
// ------------------------------------------------------- private.variables -- 
	
	static Log* log;
	
// ------------------------------------------------------- private.functions -- 
	
	std::unique_ptr<NodeTree>  parseFile(IParser* parser);
	
public:
	ParserManager();
	virtual ~ParserManager();
};

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

class ParserManager {
	static Log* log;
public:
	bool        init();
	NodeTree*   parseFile(IParser* parser);
	TOMLTree*   parseTOMLFile(std::string const &filepath);
	YAMLTree*   parseYAMLFile(std::string const &filepath);
	std::string readShaderFile(std::string const &filepath);
	
	ParserManager();
	~ParserManager();
};

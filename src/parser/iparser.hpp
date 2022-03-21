#pragma once

#include <memory>
#include <string>

#include "node.hpp"

class IParser {
public:
	virtual std::unique_ptr<Node>  run() = 0;
	
	IParser() {}
	IParser(std::string const &filepath) : filepath(filepath) {}
	virtual ~IParser() {}
protected:
	std::string  filepath;
	
	virtual std::unique_ptr<Node>  parse(std::string const &filepath) = 0;
};
#pragma once

#include <string>

#include "node.hpp"

class IParser {
public:
	virtual NodeTree* parse(std::string const &filepath) = 0;
	virtual NodeTree* run() = 0;
	IParser() {}
	IParser(std::string const &filepath) : filepath(filepath) {}
	virtual ~IParser() {}
protected:
	std::string filepath;
};
#pragma once

#include "log.hpp"

class UseLog {
	
protected:
	static Log  *log;
	
public:
	UseLog();
	virtual ~UseLog();
};
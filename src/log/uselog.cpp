
#include "uselog.hpp"

Log* UseLog::log 
	{nullptr};

UseLog::UseLog() 
	{log = Log::get();}

UseLog::~UseLog() 
	{}
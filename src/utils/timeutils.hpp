#pragma once

#ifndef TIME_HPP
#define TIME_HPP

#include <chrono>
#include <iostream>
#include <string>

inline std::string getTimeAsFormatedString(const char* format) {
	time_t now = time(NULL);
	tm lt = *localtime(&now);
	char timeString[25];
	sprintf(timeString, format, lt.tm_year + 1900, lt.tm_mon + 1, lt.tm_mday, 
											lt.tm_hour, lt.tm_min, lt.tm_sec);
	return timeString;
}

#endif /* TIME_HPP */
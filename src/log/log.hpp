#pragma once

#ifndef LOG_HPP
#define LOG_HPP

#include <fstream>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <cstdarg>

#include "../utils/timeutils.hpp"

class Log
{
public:
	
	// -------------------------------------------------------- public:Enums -- 
	enum class LogStages {
		LOG_INFO,
		LOG_WARN,
		LOG_ERROR,
		LOG_DEBUG,
		LOG_MORE,
		LOG_BEGIN,
		LOG_DONE
	};
	
	// ---------------------------------------------------- public:Functions -- 
	static Log* get();
	static void release();
	
	bool init();
	void setFileExtension(const char* extension);
	
	template <typename... Args>
	bool info (Args&& ...args) {
		return write(LogStages::LOG_INFO,  std::forward<Args>(args)...);
	}
	
	template <typename... Args>
	bool warn (Args&& ...args) {
		return write(LogStages::LOG_WARN,  std::forward<Args>(args)...);
	}
	
	template <typename... Args>
	bool error (Args&& ...args) {
		return write(LogStages::LOG_ERROR, std::forward<Args>(args)...);
	}
	
	template <typename... Args>
	bool debug (Args&& ...args) {
		return write(LogStages::LOG_DEBUG, std::forward<Args>(args)...);
	}
	
	template <typename... Args>
	bool more (Args&& ...args) {
		return write(LogStages::LOG_MORE,  std::forward<Args>(args)...);
	}
	
	template <typename... Args>
	bool begin (Args&& ...args) {
		return write(LogStages::LOG_BEGIN, std::forward<Args>(args)...);
	}
	
	template <typename... Args>
	bool done (Args&& ...args) {
		return write(LogStages::LOG_DONE,  std::forward<Args>(args)...);
	}
	
	
private:
	// --------------------------------------------------- private:Variables -- 
	static Log* _instance;
//	static std::mutex _mutex;
	
//	FILE* file{nullptr};
	
	std::string logsDirPath {"../logs"};
	std::string lastLogFilename;
	std::string logFileExtension {"log"};
//	std::queue<int> _queue;
	
	// --------------------------------------------------- private:Functions -- 
	bool write(LogStages logStage, const char* message...) const;
	
	Log();
	Log(Log &other) = delete;
	Log(std::string const &dirpath);
	~Log();
	
	Log& operator=(const Log&) = delete;
};

#endif /* LOG_HPP */

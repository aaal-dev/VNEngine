#include "log.hpp"

Log* Log::_instance = nullptr;


// --------------------------------------------------------------------- Log -- 

Log::Log () {}

Log::Log (std::string const &dirpath) : logsDirPath(dirpath) {}

Log::~Log () {}

// -------------------------------------------------------------- public:Log -- 

Log* Log::get () {
	if (_instance == nullptr)
		_instance = new Log;
	return _instance;
}

void Log::release () {
	if (_instance != nullptr)
		delete _instance;
	_instance = nullptr;
}

bool Log::init () {
	lastLogFilename = getTimeAsFormatedString("%04u.%02u.%02u-%02u:%02u:%02u") + 
														"." + logFileExtension;
	std::string logFilePath = logsDirPath + "/" + lastLogFilename;
	FILE* file = fopen(logFilePath.data(), "w");
	if (!file) {
		fprintf (stderr, "ERROR: could not open log file %s for writing\n", 
															logFilePath.data());
		return false;
	};
	bool result = write(LogStages::LOG_INFO, "log started");
	fclose (file);
	return result;
}

void Log::setFileExtension (const char* extension) {
	
}

// ------------------------------------------------------------- private:Log -- 

bool Log::write (LogStages logStage, const char* message...) const{
	va_list argptr;
	std::string logFilePath = logsDirPath + "/" + lastLogFilename;
	FILE* file = fopen(logFilePath.data(), "a");
	if (!file) {
		fprintf (stderr, "ERROR: could not open log file %s for appending\n", 
															logFilePath.data());
		return false;
	};
	std::string time = getTimeAsFormatedString("%04u/%02u/%02u %02u:%02u:%02u");
	switch (logStage) {
		case LogStages::LOG_INFO: {
			fprintf (file, "%s  [INFO]  ", time.data());
			break;
		}
		case LogStages::LOG_WARN: {
			fprintf (file, "%s  [WARN]  ", time.data());
			break;
		}
		case LogStages::LOG_ERROR: {
			fprintf (file, "%s [ERROR]  ", time.data());
			break;
		}
		case LogStages::LOG_DEBUG: {
			fprintf (file, "%s [DEBUG]  ", time.data());
			break;
		}
		case LogStages::LOG_MORE: {
			fprintf (file, "                             ");
			break;
		}
		case LogStages::LOG_BEGIN: {
			fprintf (file, "%s <[INFO]  ", time.data());
			break;
		}
		case LogStages::LOG_DONE: {
			fprintf (file, "%s  [INFO]> ", time.data());
			break;
		}
		default: break;
	}
	va_start (argptr, message);
	vfprintf (file, message, argptr);
	va_end (argptr);
	if (logStage == LogStages::LOG_ERROR) {
		va_start (argptr, message);
		vfprintf (stderr, message, argptr);
		fprintf (stderr, "%s", "\n");
		va_end (argptr);
	}
	fprintf (file, "%s", "\n");
	fclose (file);
	return true;
}

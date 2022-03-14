#include "timemanager.hpp"

TimeManager* TimeManager::_instance = nullptr;
Log* TimeManager::log = nullptr;
//ConfigManager* TimeManager::configManager = nullptr;

// ------------------------------------------------------------- TimeManager -- 

TimeManager::TimeManager () {
	log = Log::get();
//	configManager = ConfigManager::get();
//	config = configManager->createConfig("Time");
	_currentTime = glfwGetTime();
	_deltaTime = 0.0f;
	_lastTime = 0.0f;
}

TimeManager::~TimeManager () {}

// ------------------------------------------------------ public:TimeManager -- 

TimeManager* TimeManager::get () {
	if (_instance == nullptr)
		_instance = new TimeManager();
	return _instance;
}

void TimeManager::release () {
	if (_instance != nullptr)
		delete _instance;
	_instance = nullptr;
}

bool TimeManager::init () {
	return true;
}

void TimeManager::run () {
	
}

bool TimeManager::update () {
	_currentTime = glfwGetTime();
	_deltaTime = _currentTime - _lastTime;
	_lastTime = _currentTime;
	_frames++;
	if(_deltaTime >= 0.25) {
		std::cout << _frames << std::endl;
		_frames = 0;
	} else {
		_frames++;
	}
	return true;
}

double TimeManager::deltaTime () {
	return _deltaTime;
}

// ----------------------------------------------------- private:TimeManager -- 

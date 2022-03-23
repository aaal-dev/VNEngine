#include "eventmanager.hpp"


EventManager::EventMap EventManager::events;

EventManager::EventManager() {}

EventManager::~EventManager() {}

void EventManager::addEvent
(std::string const &eventName, std::unique_ptr<Event> event) {
	if (events.find(eventName) != events.end()) {
		log->warn("Event existed in delegate list");
		return;
	}
	
	events.insert({eventName, std::move(event)});
}



void EventManager::execEvent(std::string const &eventName) {
	if (events.find(eventName) != events.end()) {
		events[eventName]->exec();
	}
}
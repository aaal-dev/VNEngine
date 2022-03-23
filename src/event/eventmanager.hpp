#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

#include "../log/uselog.hpp"

#include "event.hpp"
#include "ieventcallback.hpp"

class EventManager : public UseLog {
	using EventMap = std::unordered_map<std::string, std::unique_ptr<Event>>;
public:
	void addEvent(std::string const &eventName, std::unique_ptr<Event> event);
	
	template <typename T>
	void addCallbackToEvent
	(std::string const &eventName, std::unique_ptr<IEventCallback> callback) {
		if (events.find(eventName) == events.end())	{
			log->warn("Event doesn't exist in delegate list");
			return;
	}
	auto event = dynamic_cast<Event*>(events[eventName].get());
	event->addCallback(std::move(callback));
}
	
	void execEvent(std::string const &eventName);

private:
	static EventMap events;

public:
	EventManager();
	virtual ~EventManager();

};


#include "event.hpp"


Event::Event() {}

Event::~Event(){}

void Event::addCallback(std::unique_ptr<IEventCallback> callback) {
	auto position = find(callbacks.begin(), callbacks.end(), callback);
	if (position != callbacks.end()) {
		log->warn("Action existed in delegate list");
		return;
	}
	callbacks.push_back(std::move(callback));
}
 
void Event::removeCallback(std::unique_ptr<IEventCallback> callback) {
	auto position = find(callbacks.begin(), callbacks.end(), callback);
	if (position == callbacks.end())
		return;
	callbacks.erase(position);
}
 
void Event::exec() {
	for (auto &callback : callbacks) {
		(*callback)();
	}
}
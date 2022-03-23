#pragma once

#include <memory>

#include "ieventcallback.hpp"

template<typename T>
class EventCallback : public IEventCallback 
{
public:
	void operator () () override { (instance->*function)(); }
	
	virtual bool operator == (IEventCallback* other) override
	{
		EventCallback* otherEventCallback = dynamic_cast<EventCallback*>(other);
		
		if (otherEventCallback == nullptr) return false;
		
		return
			(this->function == otherEventCallback->function) && 
			(this->instance == otherEventCallback->instance);
	}
	
private:
	T* instance;
	void (T::*function)();
	
public:
	EventCallback(T* instance, void (T::*function)())
		: instance(instance), function(function) {}
};


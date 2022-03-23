#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include "../log/uselog.hpp"

#include "ieventcallback.hpp"


class Event : public UseLog
{
	using CallbackArray = std::vector<std::unique_ptr<IEventCallback>>;
	
public:
	virtual void 
	addCallback	(std::unique_ptr<IEventCallback> callback); //override;
	virtual void 
	removeCallback (std::unique_ptr<IEventCallback> callback); //override;
	virtual void exec();
	
private:
	CallbackArray callbacks;
	
public:
	Event();
	virtual ~Event();
};


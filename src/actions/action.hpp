#pragma once

#include <functional>
#include <memory>

#include "../event/eventmanager.hpp"

#include "iaction.hpp"

namespace actions {

class Action : public IAction 
{
public:
	void exec() override { action(); }
	
//	virtual bool operator == (IAction* other) override
//	{
//		Action* otherAction = dynamic_cast<Action*>(other);
//		
//		if (otherAction == nullptr) return false;
//		
//		return (this->action == otherAction->action);
//	}
	
private:
	std::function<void()> action;
	
	
public:
	Action(std::function<void()> action) : action(action) {};
};

}
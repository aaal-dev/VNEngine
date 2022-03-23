#pragma once

#include "../../actions/iaction.hpp"

namespace cob {

class Key {
public:
	void press();
	void release();
	
	void setAction(actions::IAction* action);
	
private:
	
	actions::IAction* action;
	bool pressed {false};
	
public:
	Key();
	virtual ~Key();

};

}


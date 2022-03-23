#pragma once

namespace actions {

class IAction {
public:
	virtual void exec() = 0;
//	virtual void operator() () = 0;
//	virtual bool operator == (IAction* other) = 0;
};

}
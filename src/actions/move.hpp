#pragma once

#include "iaction.hpp" 

namespace actions
{

class Move : public IAction
{
public:
	virtual void exec();
	
	Move();
	virtual ~Move();

};

}


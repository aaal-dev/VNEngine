#pragma once

#include <string>

#include "iproperty.hpp"

namespace acb
{

template <typename T>
struct Property : public IProperty {
	T value;
	Property(std::string const &name) : IProperty(name) {};
	Property(std::string const &name, PropertyType const &type) 
		: IProperty(name, type) {};
	Property(std::string const &name, PropertyType const &type, T const &value) 
		: IProperty(name, type), value(value) {};
	virtual ~Property(void) {};
};

}


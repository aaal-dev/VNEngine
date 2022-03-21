#pragma once

#include <string>

namespace acb {

enum class PropertyType {
	NO_TYPE,
	BOOL_TYPE,
	CHAR_TYPE,
	INT_TYPE,
	DOUBLE_TYPE,
	STRING_TYPE
};

struct IProperty {
	std::string name;
	PropertyType type;
	IProperty(std::string const &name)
		: name(name), type(PropertyType::NO_TYPE) {};
	IProperty(std::string const &name, PropertyType const &type)
		: name(name), type(type) {};
	virtual ~IProperty(void) {};
};

}

#pragma once

#include <unordered_map>
#include <string>
#include <vector>

#include "../utils/text.hpp"
#include "../parser/node.hpp"

#include "property.hpp"

namespace acb
{

class Section
{
/***
 * Implements storage to collect properties with various types by specified   
 * section and gives access to them only through a section interface
 * */
public:
	// ---------------------------------------------------- public.functions -- 
	void insert (IProperty* property);
	
	void addProperty(std::string const &name);
	
	template <typename T>
	void addProperty(std::string const &name, T const &value);
	
	template <typename T>
	T getValue (std::string const &name) {
		Property<T>* property = dynamic_cast<Property<T>*>(find(name));
		return property->value;
	}
	
	template <typename T>
	void setValueInProperty (std::string const &name, T const &value) {
		dynamic_cast<Property<T>*>(find(name))->value = value;
	}
	
	void setValueFromString(IProperty *property, std::string &str);
	
	IProperty* find(std::string const &name) const;
	
	// Collects data from NodeTree, but takes only data that contains same  
	// naming of properties, and skips other
	void fill(NodeTree* tree);
	
	
private:
	// --------------------------------------------------- private.variables -- 
	std::string _name;
	std::vector <std::string> list;
	std::vector <IProperty*> properties;
	std::unordered_map <std::string, uint> indices;
	
	
public:
	Section(std::string const &name);
	Section(Section const &rhs) = delete;
	Section& operator=(Section const &rhs) = delete;
	virtual ~Section(void);
};

}


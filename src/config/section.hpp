#pragma once

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include "../utils/textutils.hpp"
#include "../parser/node.hpp"

#include "property.hpp"

namespace acb {

/**
 * @class Section
 * @author drumbox
 * @date 19/03/22
 * @file section.hpp
 * @brief Storage conntainer for properties
 *
 * Implements storage to collect properties with various types by specified
 * section and gives access to them only through a section interface
 * */

class Section {
public:
// -------------------------------------------------------- public.functions --

	void  insert(std::unique_ptr<IProperty> property);
	
	void  addProperty(std::string const &name);
	
	template <typename T>
	void  addProperty(std::string const &name, T const &value);
	
	template <typename T>
	T  getValue(std::string const &name) {
		auto property = static_cast<Property<T>*>(find(name));
		return property->value;
	}
	
	template <typename T>
	void  setValueInProperty(std::string const &name, T const &value) {
		auto property = static_cast<Property<T>*>(find(name));
		property->value = value;
	}
	
	void setValueFromString(IProperty *property, std::string &str);
	
	IProperty*  find(std::string const &name) const;
	
	/**
	 * @brief Collects data from NodeTree, but takes only data that contains
	 * same naming of properties, and skips other
	 * @param tree
	 */
	void  fill(NodeTree* tree);
	
	
private:
// ------------------------------------------------------- private.variables --

	std::string  _name;
	std::vector <std::string>  list;
	std::vector <std::unique_ptr<IProperty>>  properties;
	std::unordered_map <std::string, uint>  indices;
	
public:
	Section(std::string const &name);
	Section(Section const &rhs) = delete;
	virtual ~Section();
	
	Section& operator= (Section const &rhs) = delete;
};

}

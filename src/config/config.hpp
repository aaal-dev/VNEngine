#pragma once

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include "../parser/node.hpp"

#include "section.hpp"
#include "property.hpp"

// ----------------------------------------------------------- namespace.acb --
namespace acb {

/**
 * @class Config
 * @author drumbox
 * @date 18/03/22
 * @file config.hpp
 * @brief
 *
 * Implements storage to collect settings into individual sections of properties
 * and gives access to them only where a section was created.
 */

class Config {
	using Index = std::unordered_map<std::string, unsigned int>;
public:
// -------------------------------------------------------- public.functions --
	/**
	 * @brief Creates a new section of properties
	 * @param name Name of a section that needs to create
	 * @return Pointer to a new section data
	 */
	Section* create(std::string const &name);
	
	/**
	 * @brief Finds a existing section of properties
	 * @param name Name of a section that needs to find
	 * @return Pointer to a found section data or nullptr
	 */
	Section* find(std::string const &name) const;
	
	/**
	 * @brief Collects data from NodeTree, but takes only data that contains
	 * same naming of sections, and skips other
	 * @param tree Container
	 */
	void fill(NodeTree* tree);
	
private:
// ------------------------------------------------------- private.variables --
	std::string _name;
	std::vector <std::string> list;
	std::vector <std::unique_ptr<Section>> sections;
	Index indices;
	
public:
	Config();
	~Config();
	
};

}

#pragma once

#include <unordered_map>
#include <string>
#include <vector>

#include "../parser/node.hpp"

#include "section.hpp"
#include "property.hpp"

/***
 * Implements storage to collect settings into individual sections of properties 
 * and gives access to them only where a section was created.
 * */


namespace acb
{

class Config {
public:
	// ---------------------------------------------------- public.functions -- 
	Section* createSection(std::string const &name);
	Section* find(std::string const &name) const;
	std::vector<std::string> getListOfSections() const;
	
	// Collects data from NodeTree, but takes only data that contains same  
	// naming of sections, and skips other
	void fill(NodeTree* tree);
	
	// TODO: (1) Class must restrict insertion. Only inside creation is allowed
	// void insert(Section* section);
	
	// TODO: (2) Class must only collect data, without possibility to delete it
	// void remove(Section* section);
	
private:
	// --------------------------------------------------- private.variables -- 
	std::string _name;
	std::vector <std::string> list;
	std::vector <Section*> sections;
	std::unordered_map <std::string, uint> indices;
	
	
public:
	Config();
	~Config();
	
};

}
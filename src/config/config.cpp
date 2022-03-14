#include "config.hpp"

// ------------------------------------------------------------------ Config -- 

acb::Config::Config() {}
acb::Config::~Config() {}

// ----------------------------------------------------------- public.Config -- 

acb::Section* acb::Config::createSection(std::string const &name) {
	Section* section = new Section(name);
	indices.insert(std::make_pair(name, indices.size()));
	list.push_back(name);
	sections.push_back(section);
	return section;
}

acb::Section* acb::Config::find (std::string const &name) const {
	return sections[indices.find(name)->second];
}

std::vector<std::string> acb::Config::getListOfSections () const {
	return list;
}

void acb::Config::fill (NodeTree* tree) {
	for (auto sectionName : list) {
		// [auto] is [std::map<std::string, uint>::iterator]
		auto node = tree->search(sectionName);
		if (node != nullptr) {
			find(sectionName)->fill(node);
		}
	}
}


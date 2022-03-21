#include "config.hpp"

// ------------------------------------------------------------------ Config --

acb::Config::Config() {}
acb::Config::~Config() {}

// ----------------------------------------------------------- public.Config --

acb::Section* acb::Config::create(std::string const &name) {
	indices.insert({name, indices.size()});
	list.push_back(name);
	sections.push_back(std::make_unique<Section>(name));
	return sections.back().get();
}

acb::Section* acb::Config::find(std::string const &name) const {
	return sections[indices.find(name)->second].get();
}

void acb::Config::fill(NodeTree* tree) {
	for(auto sectionName : list) {
		auto node = tree->find(sectionName);
		
		if(node != nullptr)
			find(sectionName)->fill(node);
	}
}

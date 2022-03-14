#include "section.hpp"

// ----------------------------------------------------------------- Section -- 

acb::Section::Section(std::string const &name) : _name(name) {};
acb::Section::~Section(){}

// ---------------------------------------------------------- public.Section -- 

void acb::Section::insert (IProperty* property) {
	indices.insert(std::make_pair(property->name, indices.size()));
	list.push_back(property->name);
	properties.push_back(property);
}

void acb::Section::addProperty (std::string const &name){
	insert(new IProperty(name));
}

template <>
void acb::Section::addProperty (std::string const &name, bool const &value){
	insert(new Property<bool>(name, PropertyType::BOOL_TYPE, value));
}

template <>
void acb::Section::addProperty (std::string const &name, int const &value){
	insert(new Property<int>(name, PropertyType::INT_TYPE, value));
}

template <>
void acb::Section::addProperty (std::string const &name, double const &value){
	insert(new Property<double>(name, PropertyType::DOUBLE_TYPE, value));
}

template <>
void acb::Section::addProperty 
	(std::string const &name, std::string const &value) {
	insert(new Property<std::string>(name, PropertyType::STRING_TYPE, value));
}

void acb::Section::setValueFromString (IProperty* property, std::string &str) {
	switch (property->type) {
		case (PropertyType::BOOL_TYPE):
			str = textutils::lowercase(str);
			if (str.compare("true") == 0 || 
				str.compare("yes") == 0  || 
				str.compare("on") == 0) 
			{
				dynamic_cast<Property<bool>*>(property)->value = true;
			} else {
				dynamic_cast<Property<bool>*>(property)->value = false;
			}
			break;
		case (PropertyType::CHAR_TYPE):
			dynamic_cast<Property<const char*>*>(property)->value = str.data();
			break;
		case (PropertyType::INT_TYPE):
			dynamic_cast<Property<int>*>(property)->value = std::stoi(str);
			break;
		case (PropertyType::DOUBLE_TYPE):
			dynamic_cast<Property<double>*>(property)->value = std::stod(str);
			break;
		case (PropertyType::STRING_TYPE):
			dynamic_cast<Property<std::string>*>(property)->value = str;
			break;
		default:
			break;
	}
}

acb::IProperty* acb::Section::find (std::string const &name) const {
	return properties[indices.find(name)->second];
}

void acb::Section::fill (NodeTree* tree) {
	for (auto propertyName : list) {
		// [auto] is [std::map<std::string, uint>::iterator]
		auto node = tree->search(propertyName);
		if (node != nullptr) {
			setValueFromString(find(propertyName), node->value);
		}
	}
}
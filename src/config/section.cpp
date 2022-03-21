#include "section.hpp"

// ----------------------------------------------------------------- Section --

acb::Section::Section(std::string const &name) : _name(name) {};
acb::Section::~Section() {}

// ---------------------------------------------------------- public.Section --

void acb::Section::insert(std::unique_ptr<IProperty> property) {
	indices.insert({property->name, indices.size()});
	list.push_back(property->name);
	properties.emplace_back(std::move(property));
}

void acb::Section::addProperty(std::string const &name)
	{insert(std::make_unique<IProperty>(name));}

template <>
void acb::Section::addProperty(std::string const &name, bool const &value) {
	insert
		(std::make_unique<Property<bool>> 
			(name, PropertyType::BOOL_TYPE, value));
}

template <>
void acb::Section::addProperty(std::string const &name, int const &value) {
	insert
		(std::make_unique<Property<int>> 
			(name, PropertyType::INT_TYPE, value));
}

template <>
void acb::Section::addProperty(std::string const &name, double const &value) {
	insert
		(std::make_unique<Property<double>> 
			(name, PropertyType::DOUBLE_TYPE, value));
}

template <>
void acb::Section::addProperty
(std::string const &name, std::string const &value) {
	insert
		(std::make_unique<Property<std::string>> 
			(name, PropertyType::STRING_TYPE, value));
}

void acb::Section::setValueFromString(IProperty* property, std::string &str) {
	switch(property->type) {
		case(PropertyType::BOOL_TYPE):
			TextUtils::toLowerCase(str);
			
			if(str.compare("true") == 0
			   || str.compare("yes") == 0
			   || str.compare("on") == 0) 
				{static_cast<Property<bool>*>(property)->value = true;} 
			else 
				{static_cast<Property<bool>*>(property)->value = false;}
			
			break;
			
		case(PropertyType::CHAR_TYPE):
			static_cast<Property<const char*>*>(property)->value = str.data();
			break;
			
		case(PropertyType::INT_TYPE):
			static_cast<Property<int>*>(property)->value = std::stoi(str);
			break;
			
		case(PropertyType::DOUBLE_TYPE):
			static_cast<Property<double>*>(property)->value = std::stod(str);
			break;
			
		case(PropertyType::STRING_TYPE):
			static_cast<Property<std::string>*>(property)->value = str;
			break;
			
		default:
			break;
	}
}

acb::IProperty* acb::Section::find(std::string const &name) const 
	{return properties[indices.find(name)->second].get();}

void acb::Section::fill(NodeTree* tree) {
	for(auto propertyName : list) {
		auto node = tree->find(propertyName);
		
		if(node != nullptr) 
			{setValueFromString(find(propertyName), node->value);}
	}
}

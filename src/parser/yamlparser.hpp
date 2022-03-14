#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "yaml/yaml.h"

#include "../log/log.hpp"

#include "iparser.hpp"
#include "node.hpp"

class YAMLParser : public IParser{
	class Parser final {
		bool           _done;
		yaml_parser_t  _parser;
		bool           _hasEvent;
		static int      readHandler(void* stream_ptr, unsigned char* buffer, size_t size, size_t* size_read);
	
	public:
		yaml_event_t   _event;
		void            next();
		bool            done() const;
		
		                Parser(std::istream &stream);
		               ~Parser();
	};
	
	static Log*     log;
	bool           _iskey {false};
	bool           _isvalue {false};
	virtual void    parseLoop(YAMLParser::Parser &parser, Node* node);

public:
	virtual NodeTree* parse(std::string const &filepath) override;
	virtual NodeTree* run() override;
	
	YAMLParser();
	YAMLParser(std::string const &filepath);
	virtual ~YAMLParser();
};


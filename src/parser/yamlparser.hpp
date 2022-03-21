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
		bool  _done;
		yaml_parser_t  _parser;
		bool  _hasEvent;
		static int  readHandler(void* stream_ptr, unsigned char* buffer, size_t size, size_t* size_read);
	
	public:
		yaml_event_t  _event;
		void  next();
		bool  done() const;
		
		Parser(std::istream &stream);
		virtual ~Parser();
	};
	
public:
// -------------------------------------------------------- public.variables -- 
// -------------------------------------------------------- public.functions -- 
	
	virtual std::unique_ptr<YAMLTree>  run() override;
	
private:
// ------------------------------------------------------- private.variables -- 
	
	static Log  *log;
	bool  _iskey {false};
	bool  _isvalue {false};
	std::unique_ptr<Node>  _nodes;
	
// ------------------------------------------------------- private.functions --
	
	virtual std::unique_ptr<YAMLTree>  parse(std::string const &filepath) override;
	virtual void  parseLoop(YAMLParser::Parser &parser, Node* node);
	
public:
	YAMLParser();
	YAMLParser(std::string const &filepath);
	virtual ~YAMLParser();
};


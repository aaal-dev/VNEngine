#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../log/log.hpp"
#include "../utils/text.hpp"

#include "iparser.hpp"
#include "node.hpp"

class TOMLParser : public IParser {
	class Parser final {
		std::istream*  file;
		bool          _done;
		
	public:
		std::string    line;
		int            lineNumber;
		
		void           nextline();
		bool           done() const;
		void           removeCR(std::string &line);
		
		               Parser(std::istream &stream);
		virtual       ~Parser();
	};
	
	// Variables
	static Log*     log;
	bool           _issection {false};
	bool           _iskey {false};
	bool           _isvalue {false};
	int            _error {0};
	
	// Functions
	void            parserLoop(Parser &parser, Node* &node);
	void            proceed(Parser &parser, Node* &node, bool issection,
                            std::string &key, std::string &value,
	                        Node::NodeType type);
	void            trimLeft(std::string &line, const char* &left);
	void            trimRight(std::string &line, const char* &right);
	void            trimComment(std::string &line);
	void            trimLine(std::string &line, 
	                         const char* &left, const char* &right);
	
public:
	// Variables
	NodeTree* tree;
	
	// Functions
	virtual NodeTree* parse(std::string const &filepath) override;
	virtual NodeTree* run() override;
	
	TOMLParser();
	TOMLParser(std::string const &filepath);
	virtual ~TOMLParser();
};

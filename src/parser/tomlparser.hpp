#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../log/log.hpp"
#include "../utils/textutils.hpp"

#include "iparser.hpp"
#include "node.hpp"

/**
 * @class TOMLParser
 * @author drumbox
 * @date 19/03/22
 * @file tomlparser.hpp
 * @brief 
 */

class TOMLParser : public IParser {
	class Parser final {
		std::istream*  file;
		bool  _done {false};
		
	public:
		std::string  line;
		int  lineNumber {0};
		
		void  nextline();
		bool  done() const;
		void  removeCR(std::string &line);
		
		Parser(std::istream &stream);
		virtual ~Parser();
	};
	
	
public:
// -------------------------------------------------------- public.variables -- 
	
	TOMLTree*  tree;
	
// -------------------------------------------------------- public.functions -- 
	
	/**
	 * @brief 
	 * @return 
	 */
	virtual std::unique_ptr<TOMLTree>  run() override;
	
private:
// ------------------------------------------------------- private.variables -- 
	
	static Log  *log;
	bool  _issection {false};
	bool  _iskey {false};
	bool  _isvalue {false};
	int  _error {0};
	
// ------------------------------------------------------- private.functions -- 
	
	virtual std::unique_ptr<TOMLTree>  parse(std::string const &filepath) override;
	void  parserLoop(Parser &parser, Node *node);
	void  proceed(Parser &parser, Node *node, bool issection, 
		std::string &key, std::string &value, Node::NodeType type);
	void  trimLeft(std::string &line, const char* &left);
	void  trimRight(std::string &line, const char* &right);
	void  trimComment(std::string &line);
	void  trimLine(std::string &line, const char* &left, const char* &right);
	
public:
	TOMLParser();
	TOMLParser(std::string const &filepath);
	virtual ~TOMLParser();
};

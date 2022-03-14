// TODO Собирать все строки, кроме пустых. Строки без важной информации 
//      определять как мусорные
// TODO Переводить текст в строчный формат для избавления разночтений

#include "tomlparser.hpp"

Log* TOMLParser::log = nullptr;

const char* WHITESPACE = " \t";
const char* commentline = ";#";

//// ==== TOMLParser ====================================================== ////

TOMLParser::TOMLParser () {
	log = Log::get();
	log->info("Start TOML parser...");
}

TOMLParser::TOMLParser (std::string const &filepath) : IParser(filepath) {
	log = Log::get();
	log->info("Start TOML parser...");
}

TOMLParser::~TOMLParser () {}

NodeTree* TOMLParser::parse (std::string const &filepath) {
	std::ifstream file(filepath, std::ios::binary);
	if (!file.is_open()) {
		log->error("TOMLParser: could not open file %s for reading", 
		          filepath.data());
		return nullptr;
	}
	
	Parser parser(file);
	parser.nextline();
	if (parser.lineNumber == 1) {
		if ((unsigned char)parser.line[0] == 0xEF &&
			(unsigned char)parser.line[1] == 0xBB &&
			(unsigned char)parser.line[2] == 0xBF) 
		{
			parser.line += 3;
		}
	}
	
	NodeTree* tree = new NodeTree();
	parserLoop(parser, tree);
	tree->type = NodeTree::NodeType::ROOT_NODE;
	
	file.close();
	return tree;
}

NodeTree* TOMLParser::run() {
	return parse(filepath);
}

void TOMLParser::parserLoop (TOMLParser::Parser &parser, Node* &node) {
	bool isdone = false;
	while (!(parser.done() || isdone)) {
		trimLeft(parser.line, WHITESPACE);
		if (parser.line[0] == ';' || parser.line[0] == '#') {
			/***
			 * Skipping lines of comments. Just do nothing. 
			 * */
			 parser.nextline();
		} else if (parser.line[0] == '[') {
			/***
			 * Determinating section of properties. Must be [name]
			 * Try to get name of the section and create the object.
			 * If section is determinated, start new parserLoop to get 
			 * properties
			 * */
			
			trimComment(parser.line);
			const auto lastChar = parser.line.find_first_of("]");
			if (lastChar != std::string::npos && _issection == false) {
				// Section determinated. Proceed line as branch
				_issection = true;
				std::string name = parser.line.substr(1, lastChar-1);
				trimRight(name, WHITESPACE);
				std::string value = "";
				proceed(parser, node, true, name, value, Node::NodeType::BRANCH_NODE);
				continue;
			} else if (lastChar != std::string::npos && _issection == true) {
				// Next Section determinated. Exit from parserLoop
				_issection = false;
				return;
			} else {
				// Proceed line as trash type leaf
				log->error("Something wrong in line %d", parser.lineNumber);
				_error++;
				std::string name = "";
				proceed(parser, node, false, name, parser.line, Node::NodeType::TRASH_NODE);
			}
		} else if (!parser.line.empty()) {
			/***
			 * Deteminating other lines as the lines of properies, 
			 * they must be a 'key=value' pairs
			 * */
			 
			trimComment(parser.line);
			const auto equalsChar = parser.line.find_first_of("=");
			if (equalsChar != std::string::npos) {
				std::string key = parser.line.substr(0, equalsChar);
				trimRight(key, WHITESPACE);
				std::string value = parser.line.substr(equalsChar+1, 
				                                       parser.line.size()-1);
				trimLine(value, WHITESPACE, WHITESPACE);
				proceed(parser, node, false, key, value, Node::NodeType::LEAF_NODE);
			} else {
				log->error("No '=' found in line %d", parser.lineNumber);
				_error++;
				std::string name = "";
				proceed(parser, node, false, name, parser.line, Node::NodeType::TRASH_NODE);
			}
		} else if (parser.line.empty()) {
			parser.nextline();
		}
	}
}

void TOMLParser::proceed(Parser &parser, Node* &node, bool issection,
                         std::string &key, std::string &value,
	                     Node::NodeType type) {
	Node* childNode = new Node();
	auto index = node->indexes.find(key);
	if (index != node->indexes.end()) {
		childNode = node->nodes[index->second];
	}
	childNode->key = key;
	childNode->value = value;
	childNode->type = type;
	childNode->parent = node->index;
	childNode->level = node->level + 1;
	childNode->linenumber = parser.lineNumber;
	
	parser.nextline();
	if (issection) {
		parserLoop(parser, childNode);
	}
	node->insert(childNode);
}

void TOMLParser::trimLeft (std::string &line, const char* &left) {
	const auto begin = line.find_first_not_of(left);
	if (begin == std::string::npos) return;
	const auto range = line.size() - begin + 1;
	line = line.substr(begin, range);
}

void TOMLParser::trimRight (std::string &line, const char* &right) {
	const auto end = line.find_last_not_of(right);
	if (end == std::string::npos) return;
	line = line.substr(0, end + 1);
}

void TOMLParser::trimComment (std::string &line) {
	const auto end = line.find_first_of(";#");
	if (end == std::string::npos) return;
	line = line.substr(0, end);
}


void TOMLParser::trimLine 
(std::string &line, const char* &left, const char* &right) {
	const auto begin = line.find_first_not_of(left);
	if (begin == std::string::npos) return;
	const auto end = line.find_last_not_of(right);
	const auto range = end - begin + 1;
	line = line.substr(begin, range);
}

//// ==== TOMLParser::Parser ============================================== ////

TOMLParser::Parser::Parser (std::istream &stream) {
	file =  &stream;
	_done = false;
	lineNumber = 0;
}

TOMLParser::Parser::~Parser () {}

void TOMLParser::Parser::nextline () {
	if (!file->eof()) {
		std::getline(*file, line);
		removeCR(line);
		lineNumber++;
	} else {
		_done = true;
	}
}

bool TOMLParser::Parser::done () const { return _done; }

void TOMLParser::Parser::removeCR (std::string &line) {
	const auto end = line.find_last_not_of('\r');
	const auto range = end + 1;
	line = line.substr(0, range);
}

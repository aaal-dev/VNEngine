#include "yamlparser.hpp"

Log* YAMLParser::log = nullptr;


// -------------------------------------------------------------- YAMLParser --

YAMLParser::YAMLParser() {
	log = Log::get();
}

YAMLParser::YAMLParser(std::string const &filepath) : IParser(filepath) {
	log = Log::get();
}

YAMLParser::~YAMLParser() {}

// ------------------------------------------------------- public.YAMLParser --

std::unique_ptr<YAMLTree> YAMLParser::run() {
	return parse(this->filepath);
}

// ------------------------------------------------------ private.YAMLParser --

std::unique_ptr<YAMLTree> YAMLParser::parse(std::string const &filepath) {
	std::ifstream file(filepath, std::ios::binary);

	if(!file.is_open()) {
		log->error("YAMLParser: could not open file %s for reading",
		           filepath.data());
		return nullptr;
	}

	Parser parser(file);
	parser.next();
	parser.next();

	auto tree = std::make_unique<YAMLTree>();

	///@todo IMPORTANT!! Refactor whole parser to work with smart pointers
	parseLoop(parser, tree.get());

	while(tree->nodes.size() == 1 && tree->nodes[0]->key == "")
		tree = std::move(tree->nodes[0]);

	tree->type = NodeTree::NodeType::ROOT_NODE;

	file.close();
	return tree;
}

void YAMLParser::parseLoop(YAMLParser::Parser &parser, Node* node) {
	bool isdone = false;
	auto childNode = std::make_unique<Node>();

	while(!(parser.done() || isdone)) {
		parser.next();

		switch(parser._event.type) {
			case YAML_STREAM_START_EVENT:
			case YAML_STREAM_END_EVENT:
			case YAML_DOCUMENT_START_EVENT:
			case YAML_DOCUMENT_END_EVENT:
			case YAML_ALIAS_EVENT:
				break;
				
			case YAML_SEQUENCE_START_EVENT:
			case YAML_MAPPING_START_EVENT: {
				_iskey = true;
				_isvalue = false;
				parseLoop(parser, childNode.get());
				node->insert(std::move(childNode));
				node->count = node->nodes.size();
				childNode = std::make_unique<Node>();
				break;
			}
			
			case YAML_SEQUENCE_END_EVENT:
			case YAML_MAPPING_END_EVENT: {
				isdone = true;
				break;
			}
			
			case YAML_SCALAR_EVENT: {
				if(_iskey) {
					_iskey = false;
					_isvalue = true;
					childNode->key = reinterpret_cast<const char*>
						(parser._event.data.scalar.value);
					
				} else if(_isvalue) {
					_isvalue = false;
					_iskey = true;
					childNode->value = reinterpret_cast<const char*>
						(parser._event.data.scalar.value);
					node->insert(std::move(childNode));
					node->count = node->nodes.size();
					childNode = std::make_unique<Node>();
				}
				
				break;
			}
			
			default:
				throw std::logic_error("unexpected event type");
		}
	}
}

// ----------------------------------------------- private.YAMLParser.Parser --

YAMLParser::Parser::Parser(std::istream &stream) {
	_done = false;
	_hasEvent = false;

	if(yaml_parser_initialize(&_parser) == 0) {
		log->error("Parser: failed to initialize parser");
		throw std::runtime_error("YAML parser initialization failed");
	}

	yaml_parser_set_input(&_parser, readHandler, &stream);
}

YAMLParser::Parser::~Parser() {
	if(_hasEvent) {
		yaml_event_delete(&_event);
	}

	yaml_parser_delete(&_parser);
}

void YAMLParser::Parser::next() {
	if(_hasEvent) {
		yaml_event_delete(&_event);
		_hasEvent = false;
	}

	if(yaml_parser_parse(&_parser, &_event) == 0) {
		/*throw YAMLParser::ParseError(
			_parser.problem,
			_parser.problem_mark.line,
			_parser.problem_mark.column,
			_parser.context,
			_parser.context_mark.line
		);*/
	}

	_hasEvent = true;

	if(_event.type == YAML_STREAM_END_EVENT) {
		_done = true;
	}
}

bool YAMLParser::Parser::done() const {
	return _done;
}

int YAMLParser::Parser::readHandler(void* stream_ptr, unsigned char* buffer, size_t size, size_t* size_read) {
	std::istream &stream = *reinterpret_cast<std::istream*>(stream_ptr);

	if(!stream.eof()) {
		stream.read(reinterpret_cast<std::istream::char_type*>(buffer), size);
		*size_read = stream.gcount();

	} else {
		*size_read = 0;
	}

	return stream.bad() ? 0 : 1;
}

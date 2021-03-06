#include "parsermanager.hpp"

Log* ParserManager::log = nullptr;

// ----------------------------------------------------------- ParserManager -- 

ParserManager::ParserManager () {
	log = Log::get();
}

ParserManager::~ParserManager () {}

// ---------------------------------------------------- public.ParserManager -- 

bool ParserManager::init () {
	return true;
}

std::unique_ptr<TOMLTree> ParserManager::parseTOMLFile (std::string const &filepath) {
	auto parser = std::make_unique<TOMLParser>(filepath);
	return parseFile(parser.get());
}

std::unique_ptr<YAMLTree> ParserManager::parseYAMLFile (std::string const &filepath) {
	auto parser = std::make_unique<YAMLParser>(filepath);
	return parseFile(parser.get());
}

std::string ParserManager::readShaderFile (std::string const &filepath) {
	FILE* file = fopen(filepath.data(), "rb");
	
	if (file == nullptr) {
		log->error("Can't open shader file %s" , filepath.data());
		return "";
	}
	
	// Determine file size
	fseek(file, 0, SEEK_END);
	size_t size = ftell(file);
	fseek(file, 0, SEEK_SET);
	
	std::string result(size, 0);
	fread(&result[0], 1, size, file);
	
	fclose(file);
	return result;   
}

// --------------------------------------------------- private.ParserManager -- 

std::unique_ptr<NodeTree> ParserManager::parseFile(IParser* parser) {
	return parser->run();
}
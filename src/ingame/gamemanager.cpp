#include "gamemanager.hpp"

Log* GameManager::log = nullptr;

// ------------------------------------------------------------- GameManager --

GameManager::GameManager() {
	log = Log::get();

	ConfigManager manager;
	config = manager.createSection("Game");
	config->addProperty<std::string> ("gamename", "game");
	config->addProperty<std::string> ("dirpath", "../data");
	config->addProperty<std::string> ("filename", "game.data");
}

GameManager::~GameManager() {}

// ------------------------------------------------------ public.GameManager --

bool GameManager::init() {
	log->begin("GAME MANAGER initializing...");
	
	if(!objectManager.init()) return false;
	
	if(!prepareGameInfo()) {
		log->error("Something wrong with configuration files, check them");
		return false;
	}
	
	log->done("GAME MANAGER initialized");
	return true;
}

bool GameManager::prepareGameInfo() {
	auto filename = config->getValue<std::string> ("filename");
	auto dirpath = config->getValue<std::string> ("dirpath");
	auto yamltree = getYAMLTree(dirpath, filename);
	
	if(yamltree->empty()) {
		log->warn("Game not found in default diractory %s", dirpath.data());
		return false;
	}
	
	//objectManager.seekObjects(tree, dirpath);
	return true;
}

std::unique_ptr<YAMLTree> GameManager::getYAMLTree
(std::string const &dirpath, std::string const &filename) {
	std::string filepath {dirpath + "/" + filename};
	auto manager = std::make_unique<ParserManager>();
	auto yamltree = manager->parseYAMLFile(filepath);
	
	if(yamltree != nullptr) {
		yamltree->key = "file";
		yamltree->value = filename;
		yamltree->insert(std::make_unique<Node> ("filename", filename));
		yamltree->insert(std::make_unique<Node> ("path", dirpath));
		Node *foldersNode = yamltree->nodes[0]->find("folders");
		
		if(foldersNode != nullptr) {
			for(auto &folderNode : foldersNode->nodes) {
				Node *node = folderNode->find("foldername");
				
				if(node != nullptr) {
					std::string foldername = node->value;
					std::string nextDirpath = dirpath + "/" + foldername;
					std::string nextFilename = foldername + ".data";
					auto newTree = getYAMLTree(nextDirpath, nextFilename);
					
					if(newTree != nullptr) 
						folderNode->insert(std::move(newTree));
				}
			}
		}
	}
	
	return yamltree;
}

#include "gamemanager.hpp"

Log* GameManager::log = nullptr;

// ------------------------------------------------------------- GameManager -- 

GameManager::GameManager () {
	log = Log::get();
	
	ConfigManager manager;
	config = manager.createSection("Game");
	config->addProperty<std::string>("gamename", "game");
	config->addProperty<std::string>("dirpath", "../data");
	config->addProperty<std::string>("filename", "game.data");
}

GameManager::~GameManager () {}

// ------------------------------------------------------ public.GameManager -- 

bool GameManager::init () {
	log->begin("GAME MANAGER initializing...");
	if (!objectManager.init()) return false;
	
	if (!prepareGameInfo()) {
		log->error("Something wrong with configuration files, check them");
		return false;
	}
	
	log->done("GAME MANAGER initialized");
	return true;
}

bool GameManager::prepareGameInfo () {
	auto dirpath = config->getValue<std::string>("dirpath") + "/";
	auto filename = config->getValue<std::string>("filename");
	YAMLTree *tree = readYAMLFile(dirpath, filename);
	if (tree->empty()) {
		log->warn("File %s not found in %s", filename.data(), dirpath.data());
		return false;
	} else {
		objectManager.seekObjects(tree, dirpath);
	}
	return true;
}

YAMLTree* GameManager::readYAMLFile 
(std::string const &dirpath, std::string const &filename) {
	std::string filepath = dirpath + filename;
	ParserManager *manager = new ParserManager;
	YAMLTree *tree = manager->parseYAMLFile(filepath);
	if (tree != nullptr) {
		tree->key = "file";
		tree->value = filename;
		tree->insert(new Node("filename", filename));
		tree->insert(new Node("path", dirpath));
		Node *foldersNode = tree->nodes[0]->search("folders");
		if (foldersNode != nullptr) {
			for (auto folderNode : foldersNode->nodes) {
				Node *node = folderNode->search("foldername");
				if (node != nullptr) {
					std::string foldername = node->value;
					std::string nextDirpath = dirpath + foldername + "/";
					std::string nextFilename = foldername + ".data";
					YAMLTree *newTree = readYAMLFile(nextDirpath, nextFilename);
					if (newTree != nullptr) folderNode->insert(newTree);
				}
			}
		}
	}
	delete manager;
	return tree;
}

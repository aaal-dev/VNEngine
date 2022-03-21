#pragma once

#include "../log/log.hpp"
#include "../config/configmanager.hpp"

#include "objectmanager.hpp"
#include "scenemanager.hpp"

#include "../parser/node.hpp"
#include "../parser/parsermanager.hpp"

class GameManager {
public:
// -------------------------------------------------------- public.variables --
	ObjectManager objectManager;
	SceneManager sceneManager;

	FoldersTree *foldersTree;
	SceneTree *sceneTree;

// -------------------------------------------------------- public.functions --
	bool init();
	bool prepareGameInfo();
	std::unique_ptr<YAMLTree> getYAMLTree
	(std::string const &dirpath, std::string const &filename);


private:
// ------------------------------------------------------- private.variables --
	static Log *log;
	acb::Section *config {nullptr};

public:
	GameManager();
	virtual ~GameManager();
};

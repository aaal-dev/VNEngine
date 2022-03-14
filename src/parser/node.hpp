#pragma once

#include <string>
#include <unordered_map>
#include <vector>

struct Node {
	enum class NodeType {
		ROOT_NODE,
		BRANCH_NODE,
		LEAF_NODE,
		TRASH_NODE
	}; 
	
	std::string key;
	std::string value;
	NodeType type;
	uint parent {0};
	uint level {0};
	uint index {0};
	uint linenumber {0};
	uint count {0};
	
	std::unordered_map<std::string, uint> indexes;
	std::vector<Node*> nodes;
	
	void insert(Node* node);
	void remove(Node* node);
	Node* search(std::string const &key);
	bool empty();
	
	Node* operator[] (std::string const &key);
	
	Node() {};
	Node(std::string const &key, std::string const &value)
	                                               : key(key), value(value) {};
	virtual ~Node() {};
};

typedef Node NodeTree;
typedef Node TOMLTree;
typedef Node YAMLTree;
typedef Node FoldersTree;
typedef Node SceneTree;
typedef Node ObjectTree;

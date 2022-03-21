#pragma once

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

struct Node {
	using IndicesMap = std::unordered_map<std::string, unsigned int>;
	using NodePtrs = std::vector<std::unique_ptr<Node>>;
	enum class NodeType {
		ROOT_NODE,
		BRANCH_NODE,
		LEAF_NODE,
		TRASH_NODE
	}; 
	
	std::string  key;
	std::string  value;
	NodeType  type;
	unsigned int  parent {0};
	unsigned int  level {0};
	unsigned int  index {0};
	unsigned int  linenumber {0};
	unsigned int  count {0};
	
	std::unordered_map<std::string, unsigned int>  indexes;
	std::vector<std::unique_ptr<Node>>  nodes;
	
	void  insert(std::unique_ptr<Node> node);
	//void  remove(Node* node);
	Node*  find(std::string const &key);
	bool  empty();
	
	Node*  operator[](std::string const &key);
	
	Node() {}
	//Node(Node *other) : key(other->key), value(other->value) {}
	//Node(Node const &other) : key(other.key), value(other.value) {}
	Node(std::string const &key, std::string const &value)
		: key(key), value(value) {}
	virtual ~Node() {}
};

typedef Node NodeTree;
typedef Node TOMLTree;
typedef Node YAMLTree;
typedef Node FoldersTree;
typedef Node SceneTree;
typedef Node ObjectTree;

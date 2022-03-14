#include "node.hpp"

// ------------------------------------------------------------- public.Node -- 

void Node::insert(Node* node) {
	indexes.insert(std::make_pair(node->key, indexes.size()));
	nodes.push_back(node);
	count = nodes.size();
}

void Node::remove(Node* node) {
	
}

Node* Node::search(std::string const &key) {
	return (*this)[key];
}

bool Node::empty() {
	return nodes.empty();
}

Node* Node::operator[](std::string const &key) {
	auto i = indexes.find(key);
	return i == indexes.end() ? nullptr : nodes[i->second];
}

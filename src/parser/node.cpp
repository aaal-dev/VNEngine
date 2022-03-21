#include "node.hpp"

// ------------------------------------------------------------- public.Node -- 

void Node::insert(std::unique_ptr<Node> node) {
	indexes.insert({node->key, indexes.size()});
	nodes.emplace_back(std::move(node));
	count = nodes.size();
}

Node* Node::find(std::string const &key) {
	auto index = indexes.find(key);
	return index == indexes.end() ? nullptr : nodes[index->second].get();
}

bool Node::empty() {
	return nodes.empty();
}

Node* Node::operator[](std::string const &key) {
	return find(key);
}

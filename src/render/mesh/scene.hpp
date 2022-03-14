#pragma once

#include <vector>

// Inner class
#include "../../maths/maths.hpp"
#include "mesh.hpp"

class TransformationStack {
	std::vector<mat4> stack;
public:
	     void   push(mat4 &m);
	     void   pop();
	const int   size() const;
	            TransformationStack();
};

TransformationStack::TransformationStack () {
	stack.push_back(mat4::identity());
}

void TransformationStack::push (mat4 &m) {
	stack.push_back(m);
}

void TransformationStack::pop () {
	if (stack.size() > 1)
		stack.pop_back();
}

const int TransformationStack::size () const {
	return stack.size();
}

struct Scene {
	std::deque<Mesh*>   meshes;
	TransformationStack   transformationStack;
};
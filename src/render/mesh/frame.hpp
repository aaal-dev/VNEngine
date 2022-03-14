#pragma once

#include <deque>

// Inner class
#include "../../maths/maths.hpp"
#include "mesh.hpp"

class TransformationStack {
	std::vector<mat4> stack;
public:
	void   push(mat4 &m){
		stack.push_back(m);
	}
	
	void   pop() {
		if (stack.size() > 1)
			stack.pop_back();
	}
	
	const int   size() const {
		return stack.size();
	}
	
	TransformationStack() {
		stack.push_back(mat4::identity());
	}
};

struct Frame {
	TransformationStack   transformationStack;
};

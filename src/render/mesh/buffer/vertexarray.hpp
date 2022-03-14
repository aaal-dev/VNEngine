#pragma once

#include <vector>

// GLAD
#include "glad/glad.h"

// Inner classes
#include "vertexbuffer.hpp"

class VertexArray {
	GLuint _id;
	std::vector<VertexBuffer*> _buffers;
	
public:
	void generate() { glGenVertexArrays(1, &_id); }
	void destroy() const { glDeleteVertexArrays(1, &_id); }
	
	void bind() const { glBindVertexArray(_id); }
	void unbind() const { glBindVertexArray(0); }
	
	void addBuffer(VertexBuffer* buffer) { 
		_buffers.push_back(buffer);
	}
	
	
	
	inline const GLuint id() const { return _id; }
	
	VertexArray() { generate(); }
	~VertexArray() { 
		for(unsigned int i = 0; i < _buffers.size(); i++) 
			delete _buffers[i]; 
		destroy();
	}
};

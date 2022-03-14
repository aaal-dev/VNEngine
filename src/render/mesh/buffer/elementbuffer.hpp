#pragma once

// GLAD
#include "glad/glad.h"

class ElementBuffer {
	GLuint _id;
	GLuint _count;
	
public:
	void generate() { glGenBuffers(1, &_id); }
	void destroy() const { glDeleteBuffers(1, &_id); }
	
	void bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id); }
	void unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
	
	void proceed(GLvoid* data) {
		bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _count * sizeof(GLuint), data, GL_STATIC_DRAW);
		unbind();
	}
	
	void create(GLvoid* data, GLsizei count) {
		_count = count;
		proceed(data);
	}
	
	inline const GLuint id() const { return _id; }
	inline const GLuint count() const { return _count; }
	
	ElementBuffer() { generate(); }
	ElementBuffer(GLvoid* data, GLsizei count) : _count(count) {
		generate();
		proceed(data);
	}
	
	~ElementBuffer() { destroy(); }
};

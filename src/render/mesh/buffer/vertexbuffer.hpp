#pragma once

#include "glad/glad.h"

#include "../vertex.hpp"

class VertexBuffer {
	GLuint _id;
	GLuint _vertexCount;
	GLuint _componentCount;
	
public:
	void generate() { glGenBuffers(1, &_id); }
	void destroy() const { glDeleteBuffers(1, &_id); }
	
	void bind() const { glBindBuffer(GL_ARRAY_BUFFER, _id); }
	void unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
	
	void* open() { return glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY); }
	void close() { glUnmapBuffer(GL_ARRAY_BUFFER); }
	
	void proceed(GLvoid* data) {
		bind();
		glBufferData(GL_ARRAY_BUFFER, 
		            _vertexCount * sizeof(Vertex), 
		             data, 
		             GL_STATIC_DRAW);
		unbind();
	}
	
	void create(GLvoid* data, GLsizei count, GLuint componentCount) {
		_vertexCount = count;
		_componentCount = componentCount;
		proceed(data);
	}
	
	void setAttribute(GLuint location, GLuint size, GLenum type, 
	                  GLboolean normalized, const GLvoid* offset) {
		glEnableVertexAttribArray(location);
		glVertexAttribPointer(
			location, 
			size, 
			type, 
			normalized, 
			sizeof(Vertex), 
			offset
		);
	}
	
	inline const GLuint id() const { return _id; }
	inline const GLuint vertexCount() const { return _vertexCount; }
	inline const GLuint componentCount() const { return _componentCount; }
	
	VertexBuffer() { generate(); };
	VertexBuffer(GLvoid* data, GLsizei count, GLuint componentCount) 
		: _vertexCount(count), _componentCount(componentCount)
	{
		generate();
		proceed(data);
	}
	
	~VertexBuffer() { destroy(); }
};

#pragma once

#include <string>

#include "glad/glad.h"

#include "texturemanager.hpp"

class Texture {
public:
	void generate(GLenum target);
	void terminate() const;
	void   bind() const;
	void unbind() const;
	
	GLuint proceed() const;
	void load(std::string const &filepath);
	
	void setParameter(GLenum parameter, GLint value);
	void generateMipmap();
	
	inline const GLuint id() const { return _id; }
	inline const unsigned int width() const { return _width; }
	inline const unsigned int height() const { return _height; }
	inline const GLenum target() const { return _target; }
	
private:
	GLuint   _id;
	GLenum   _target;
	GLenum   _format;
	std::string   _filepath;
	int _width;
	int _height;
	int _CPP;
	
	void generate();
	
public:
	Texture();
	Texture(GLenum const &target);
	Texture(std::string const &filepath);
	Texture(GLenum const &target, std::string const &filepath);
	~Texture();
};

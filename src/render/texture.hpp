#pragma once

#include <string>

// GLAD
#include "glad/glad.h"

// stb
#include "stb/stb_image.h"

class Texture {
	GLuint   _id;
	GLenum   _target;
	std::string _filepath;
	int _width, _height, _CPP;
	
	void generate() { glGenTextures(1, &_id); }
public:
	void generate(GLenum target) { glGenTextures(1, &_id); _target = target; }
	void terminate() const { glDeleteTextures(1, &_id); }
	
	void bind()   const { glBindTexture(_target, _id); }
	void unbind() const { glBindTexture(_target,  0); }
	
	unsigned char* load() { return stbi_load(_filepath.data(), &_width, &_height, &_CPP, 0); }
	unsigned char* load(const std::string &filepath) { 
		_filepath = filepath;
		return load(); 
	}
	
	void setParameter(GLenum parameter, GLint value) { glTexParameteri(_target, parameter, value); }
	void generateMipmap() { glGenerateMipmap(_target); }
	void setTexture(GLint level, GLint iformat, GLint border, GLenum format)  {
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = load();
		glTexImage2D(_target, level, iformat, _width, _height, border, format, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
	}
	void setTexture(const std::string &filepath, GLint level, GLint iformat, GLint border, GLenum format) {
		_filepath = filepath;
		setTexture(level, iformat, border, format);
	}
	
	inline const GLuint id() const { return _id; }
	inline const unsigned int width() const { return _width; }
	inline const unsigned int height() const { return _height; }
	inline const GLenum target() const { return _target; }
	
	Texture() {}
	Texture(const GLenum &target) : _target(target) { generate(); }
	Texture(const std::string &filepath) : _filepath(filepath) {}
	Texture(const GLenum &target, const std::string &filepath) : _target(target), _filepath(filepath) { generate(); }
	~Texture() { terminate(); }
};

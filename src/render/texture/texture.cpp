#include "texture.hpp"

// ----------------------------------------------------------------- Texture -- 

Texture::Texture() { glGenTextures(1, &_id); }
Texture::Texture(GLenum const &target) : _target(target) { generate(); }
Texture::Texture(std::string const &filepath) : _filepath(filepath) {}
Texture::Texture(GLenum const &target, std::string const &filepath) 
: _target(target), _filepath(filepath) { generate(); }
Texture::~Texture() { terminate(); }

// ---------------------------------------------------------- public:Texture -- 

void Texture::generate(GLenum target) { glGenTextures(1, &_id); _target = target; }
void Texture::terminate() const { glDeleteTextures(1, &_id); }
void Texture::bind() const { glBindTexture(_target, _id); }
void Texture::unbind() const { glBindTexture(_target,  0); }

GLuint Texture::proceed() const { 
	TextureManager manager;
	return manager.create(_filepath, _target);
}

void Texture::load(std::string const &filepath) {
	_filepath = filepath;
	_target = GL_TEXTURE_2D;
	_id = proceed(); 
}

void Texture::setParameter(GLenum parameter, GLint value) { 
	glTexParameteri(_target, parameter, value); 
}

void Texture::generateMipmap() { glGenerateMipmap(_target); }

// --------------------------------------------------------- private:Texture -- 

void Texture::generate() { glGenTextures(1, &_id); }

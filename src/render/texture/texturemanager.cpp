#define STB_IMAGE_IMPLEMENTATION
#include "texturemanager.hpp"


Log* TextureManager::log = nullptr;

// ---------------------------------------------------------- TextureManager -- 

TextureManager::TextureManager () {
	log = Log::get();
}

TextureManager::~TextureManager () {
}

// --------------------------------------------------- public:TextureManager -- 

GLuint TextureManager::create (std::string const &filepath, GLenum const &target) {
	int width, height, cpp;
	unsigned char* imageData = readImageData(filepath.data(), width, height, cpp);
	GLuint iformat;
	GLenum format;
	if (cpp == 3) {
		iformat = GL_RGB;
		format = GL_RGB;
	} else if (cpp == 4) {
		iformat = GL_RGBA;
		format = GL_RGBA;
	}
	GLuint id;
	glGenTextures(1, &id);
	glBindTexture(target, id); 
	glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexImage2D(target, 0, iformat, width, height, 0, format, GL_UNSIGNED_BYTE, imageData);
	glGenerateMipmap(target);
	return id;
}

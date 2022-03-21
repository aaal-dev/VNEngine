#pragma once

#include <string>

#include "glad/glad.h"

#include "../../log/log.hpp"
#include "../../utils/image.hpp"

class TextureManager {
public:
	
	GLuint create(std::string const &filepath, GLenum const &target);
	
private:
// ------------------------------------------------------- private.variables --
	
	static Log*  log;
	
public:
	TextureManager();
	virtual ~TextureManager();
};

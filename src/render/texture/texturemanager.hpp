#pragma once

#include <string>

// GLAD
#include "glad/glad.h"

// Inner classes
#include "../../log/log.hpp"
#include "../../utils/image.hpp"

class TextureManager {
	// --------------------------------------------------- private:Variables --
	           static Log*  log;
public:
	GLuint create(std::string const &filepath, GLenum const &target);
	TextureManager();
	virtual ~TextureManager();

};


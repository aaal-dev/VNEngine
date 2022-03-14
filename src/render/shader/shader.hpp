#pragma once

#include <string>

// GLAD
#include "glad/glad.h"

// Inner classes
#include "../../maths/maths.hpp"
#include "shadermanager.hpp"

class Shader {
	     GLuint   _id;
	std::string   _vertexShaderFilepath;
	std::string   _fragmentShaderFilepath;
	std::string   _geometryShaderFilepath;
	
public:
	       void   create();
	       void   destroy() const;
	       void   enable() const;
	       void   disable() const;
	
	     GLuint   proceed() const;
	       void   load(const std::string &vertexShaderFilepath, 
	                   const std::string &fragmentShaderFilepath,
	                   const std::string &geometryShaderFilepath = "");
	       void   reload();
	
	       void   setUniform1f (const GLchar* name, float value) const;
	       void   setUniform1i (const GLchar* name, int value) const;
	       void   setUniform2f (const GLchar* name, const vec2 &vector) const;
	       void   setUniform3f (const GLchar* name, const vec3 &vector) const;
	       void   setUniform4f (const GLchar* name, const vec4 &vector) const;
	       void   setUniformMat4 (const GLchar* name, const mat4 &matrix) const;
	
	inline const GLint  getUniform(const GLchar* name) const;
	inline const GLuint id() const;
	
	Shader();
	Shader(const std::string &vertexShaderFilepath, 
	       const std::string &fragmentShaderFilepath,
	       const std::string &geometryShaderFilepath = "");
};


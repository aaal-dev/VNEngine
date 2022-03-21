#pragma once

#include <string>

#include "glad/glad.h"

#include "../../maths/maths.hpp"
#include "shadermaker.hpp"

/***
 * Contains information about shader and most important functions to work with.
 * All unnecessery functions placed in ShaderMaker class
 * */

class Shader {
public:
// -------------------------------------------------------- public.functions --
	void   create();
	void   destroy() const;
	void   enable() const;
	void   disable() const;
	
	void   load(std::string const &vertexShaderFilepath,
	            std::string const &fragmentShaderFilepath,
	            std::string const &geometryShaderFilepath = "");
	void   reload();
	
	void   setUniform1f(GLchar const *name, float value) const;
	void   setUniform1i(GLchar const *name, int value) const;
	void   setUniform2f(GLchar const *name, vec2 const &vector) const;
	void   setUniform3f(GLchar const *name, vec3 const &vector) const;
	void   setUniform4f(GLchar const *name, vec4 const &vector) const;
	void   setUniformMat4(GLchar const *name, mat4 const &matrix) const;
	
	inline const GLint  getUniform(GLchar const *name) const;
	inline const GLuint id() const;
	
private:
// ------------------------------------------------------- private.variables --
	GLuint   _id;
	std::string   _vertexShaderFilepath;
	std::string   _fragmentShaderFilepath;
	std::string   _geometryShaderFilepath;
	
// ------------------------------------------------------- private.functions --
	GLuint proceed() const;
	
public:
// ----------------------------------------------------------- public.Shader --
	Shader();
	Shader(std::string const &vertexShaderFilepath,
	       std::string const &fragmentShaderFilepath,
	       std::string const &geometryShaderFilepath = "");
	virtual ~Shader();
};

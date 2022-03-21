#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
//#include <algorithm>
#include <sstream>

#include "glad/glad.h"

#include "../../log/log.hpp"
#include "../../config/configmanager.hpp"
#include "../../maths/maths.hpp"

class ShaderMaker {
public:
// -------------------------------------------------------- public.variables --
// -------------------------------------------------------- public.functions --
	GLuint load(std::string const &filepath, GLenum shaderType);
	GLuint compile(std::string const &shaderCode, GLenum shaderType);
	GLuint link(std::string const &vertexShaderFilepath,
				std::string const &fragmentShaderFilepath,
				std::string const &geometryShaderFilepath = "");
	
	bool isValid (GLuint &shaderID);
	
private:
// ------------------------------------------------------- private.variables --
	
	static Log *log;
	
// ------------------------------------------------------- private.functions --
	
	void   logShaderInfo(GLuint &shaderID);
	void   logProgramInfo(GLuint &shaderID);
	void   logAllShaderInfo(GLuint &shaderID);
	const char*  GLtypeToString(GLenum &type);
	
public:

	ShaderMaker();
	~ShaderMaker();
};

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
#include "../../utils/fileutils.hpp"

class ShaderMaker {
public:
// -------------------------------------------------------- public.variables --
// -------------------------------------------------------- public.functions --
	/**
	 * @brief 
	 * @param vertexShaderFilepath
	 * @param fragmentShaderFilepath
	 * @param geometryShaderFilepath
	 * @return 
	 */
	GLuint make(std::string const &vertexShaderFilepath,
				std::string const &fragmentShaderFilepath,
				std::string const &geometryShaderFilepath = "");
	GLuint load(std::string const &filepath, GLenum shaderType);
	GLuint compile(std::string const &shaderCode, GLenum shaderType);
	
	bool isValid (GLuint &shaderID);
	
private:
// ------------------------------------------------------- private.variables --
	
	static Log *log;
	
// ------------------------------------------------------- private.functions --
	
	void   checkShader(GLuint &shaderID);
	void   checkProgram(GLuint &programId);
	void   logAllShaderInfo(GLuint &programId);
	const char*  GLtypeToString(GLenum &type);
	
public:

	ShaderMaker();
	~ShaderMaker();
};

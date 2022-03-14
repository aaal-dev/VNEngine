#pragma once

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
//#include <algorithm>
#include <sstream>

// GLAD
#include "glad/glad.h"

// Inner classes
#include "../../log/log.hpp"
#include "../../config/configmanager.hpp"
#include "../../maths/maths.hpp"

class ShaderManager {
	// --------------------------------------------------- private:Variables -- 
	static           Log*  log;
	static ConfigManager*  configManager;
	
	// --------------------------------------------------- private:Functions -- 
	      void   logShaderInfo(GLuint &shaderID);
	      void   logProgramInfo(GLuint &shaderID);
	      void   logAllShaderInfo(GLuint &shaderID);
	const char*  GLtypeToString(GLenum &type);
	
public:
	// ---------------------------------------------------- public:Variables -- 
	
	
	// ---------------------------------------------------- public:Functions -- 
	static void initialize();
	
	void enable() const;
	void disable() const;
	
	GLuint load(const std::string &filepath, GLenum shaderType);
	GLuint compile(const std::string &shaderCode, GLenum shaderType);
	GLuint link(const std::string &vertexShaderFilepath, 
	            const std::string &fragmentShaderFilepath,
	            const std::string &geometryShaderFilepath = "");
	
	bool isValid (GLuint &shaderID);
	
	 ShaderManager();
	~ShaderManager();
};

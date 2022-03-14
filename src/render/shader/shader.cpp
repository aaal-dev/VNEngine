#include "shader.hpp"

// ------------------------------------------------------------------ Shader -- 

Shader::Shader() {}
Shader::Shader(const std::string &vertexShaderFilepath, 
	           const std::string &fragmentShaderFilepath,
	           const std::string &geometryShaderFilepath)
	: _vertexShaderFilepath(vertexShaderFilepath), 
	  _fragmentShaderFilepath(fragmentShaderFilepath),
	  _geometryShaderFilepath(geometryShaderFilepath) {}

// ----------------------------------------------------------- public:Shader -- 

void Shader::create() { _id = glCreateProgram(); }
void Shader::destroy() const { glDeleteProgram(_id); }
void Shader::enable() const { glUseProgram(_id); };
void Shader::disable() const { glUseProgram(0); };

GLuint Shader::proceed () const {
	ShaderManager manager;
	return manager.link(_vertexShaderFilepath, _fragmentShaderFilepath);
}

void Shader::load (const std::string &vertexShaderFilepath, 
                   const std::string &fragmentShaderFilepath,
                   const std::string &geometryShaderFilepath) {
	_vertexShaderFilepath = vertexShaderFilepath;
	_fragmentShaderFilepath = fragmentShaderFilepath;
	_geometryShaderFilepath = geometryShaderFilepath;
	_id = proceed();
}

void Shader::reload () {
	GLuint newProgram = proceed();
	if (newProgram) {
		destroy();
		_id = newProgram;
	}
}

void Shader::setUniform1f (const GLchar* name, float value) const { 
	glUniform1f(getUniform(name), value); 
}

void Shader::setUniform1i (const GLchar* name, int value) const { 
	glUniform1i(getUniform(name), value); 
}

void Shader::setUniform2f (const GLchar* name, const vec2 &vector) const { 
	glUniform2f(getUniform(name), vector.x, vector.y); 
}

void Shader::setUniform3f (const GLchar* name, const vec3 &vector) const { 
	glUniform3f(getUniform(name), vector.x, vector.y, vector.z);
}

void Shader::setUniform4f (const GLchar* name, const vec4 &vector) const { 
	glUniform4f(getUniform(name), vector.x, vector.y, vector.z, vector.w); 
}

void Shader::setUniformMat4 (const GLchar* name, const mat4 &matrix) const { 
	glUniformMatrix4fv(getUniform(name), 1, GL_FALSE, matrix.elements); 
}

inline const GLint Shader::getUniform(const GLchar* name) const { 
	return glGetUniformLocation(_id, name); 
}

inline const GLuint Shader::id() const { return _id; }

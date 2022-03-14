#include "shadermanager.hpp"

Log* ShaderManager::log = nullptr;
//ConfigManager* ShaderManager::configManager = nullptr;

// ----------------------------------------------------------- ShaderManager -- 

ShaderManager::ShaderManager(){
	log = Log::get();
//	configManager = ConfigManager::get();
}

ShaderManager::~ShaderManager(){}

// ---------------------------------------------------- public:ShaderManager -- 

GLuint ShaderManager::load(std::string const &filepath, GLenum shaderType) {
	std::string shaderCode;
	std::ifstream shaderStream(filepath, std::ios::in);
	if (!shaderStream.is_open()) {
		log->error("Impossible to open %s. \
		          Are you in the right directory? \
		          Don't forget to read the FAQ !", filepath.data());
		return false;
	}
	std::stringstream sstr;
	sstr << shaderStream.rdbuf();
	shaderCode = sstr.str();
	shaderStream.close();
	
	log->info("Compiling shader : %s", filepath.data());
	return compile(shaderCode, shaderType);
}

GLuint ShaderManager::compile(std::string const &shaderCode, GLenum shaderType) {
	GLuint shaderID = glCreateShader(shaderType);
	
	const char* sourcePointer = shaderCode.data();
	glShaderSource(shaderID, 1, &sourcePointer, NULL);
	glCompileShader(shaderID);
	
	// Check Vertex Shader
	GLint result = GL_FALSE;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		log->error("Something wrong.");
	}
	logShaderInfo(shaderID);
	
	return shaderID;
}

GLuint ShaderManager::link 
(std::string const &vertexShaderFilepath, 
 std::string const &fragmentShaderFilepath,
 std::string const &geometryShaderFilepath) {
	GLuint vertexShaderID = load(vertexShaderFilepath, GL_VERTEX_SHADER);
	GLuint fragmentShaderID = load(fragmentShaderFilepath, GL_FRAGMENT_SHADER);
	GLuint geometryShaderID = 0;
	if (geometryShaderFilepath != "")
		load(geometryShaderFilepath, GL_GEOMETRY_SHADER);
	
	log->info("Linking program");
	GLuint id = glCreateProgram();
	glAttachShader(id, vertexShaderID);
	glAttachShader(id, fragmentShaderID);
	if (geometryShaderFilepath != "")
		glAttachShader(id, geometryShaderID);
	glLinkProgram(id);
	
	// Check the program
	GLint result = GL_FALSE;
	
	glGetProgramiv(id, GL_LINK_STATUS, &result);
	logProgramInfo(id);
	
//	glDetachShader(id, vertexShaderID);
//	glDetachShader(id, fragmentShaderID);
//	if (geometryShaderFilepath != "")
//		glDetachShader(id, geometryShaderID);
	
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
	if (geometryShaderFilepath != "")
		glDeleteShader(geometryShaderID);
	return id;
}

bool ShaderManager::isValid (GLuint &shaderID) {
	glValidateProgram (shaderID);
	int params = -1;
	glGetProgramiv (shaderID, GL_VALIDATE_STATUS, &params);
	log->info("program %i GL_VALIDATE_STATUS = %i", shaderID, params);
	if (GL_TRUE != params) {
		logShaderInfo (shaderID);
		return false;
	}
	return true;
}

// --------------------------------------------------- private:ShaderManager -- 

// Log functions
void ShaderManager::logShaderInfo(GLuint &shaderID) {
	int length;
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
	if ( length > 0 ){
		std::vector<char> message(length+1);
		glGetShaderInfoLog(shaderID, length, NULL, &message[0]);
		log->error("%s", &message[0]);
	}
}

void ShaderManager::logProgramInfo(GLuint &shaderID) {
	int length;
	glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &length);
	if ( length > 0 ){
		std::vector<char> message(length+1);
		glGetProgramInfoLog(shaderID, length, NULL, &message[0]);
		log->error("%s", &message[0]);
	}
}

void ShaderManager::logAllShaderInfo (GLuint &shaderID) {
	log->info("--------------------\nshader program %i info:", shaderID);
	int params = -1;
	glGetProgramiv (shaderID, GL_LINK_STATUS, &params);
	log->more("GL_LINK_STATUS = %i", params);
	
	glGetProgramiv (shaderID, GL_ATTACHED_SHADERS, &params);
	log->more("GL_ATTACHED_SHADERS = %i", params);
	
	glGetProgramiv (shaderID, GL_ACTIVE_ATTRIBUTES, &params);
	log->more("GL_ACTIVE_ATTRIBUTES = %i", params);
	for (GLuint i = 0; i < (GLuint)params; i++) {
		char name[64];
		int max_length = 64;
		int actual_length = 0;
		int size = 0;
		GLenum type;
		glGetActiveAttrib (shaderID, i, max_length, &actual_length, &size, 
		                   &type, name);
		if (size > 1) {
			for (int j = 0; j < size; j++) {
				char long_name[128];
				sprintf (long_name, "%s[%i]", name, j);
				int location = glGetAttribLocation (shaderID, long_name);
				log->more("  %i) type:%s name:%s location:%i", i, 
				         GLtypeToString (type), long_name, location);
			}
		} else {
			int location = glGetAttribLocation (shaderID, name);
			log->more("  %i) type:%s name:%s location:%i", i, 
			         GLtypeToString (type), name, location);
		}
	}
	
	glGetProgramiv (shaderID, GL_ACTIVE_UNIFORMS, &params);
	log->more("GL_ACTIVE_UNIFORMS = %i", params);
	for (GLuint i = 0; i < (GLuint)params; i++) {
		char name[64];
		int max_length = 64;
		int actual_length = 0;
		int size = 0;
		GLenum type;
		glGetActiveUniform (shaderID, i, max_length, &actual_length, &size, 
		                    &type, name);
		if (size > 1) {
			for (int j = 0; j < size; j++) {
				char long_name[128];
				sprintf (long_name, "%s[%i]", name, j);
				int location = glGetUniformLocation (shaderID, long_name);
				log->more("  %i) type:%s name:%s location:%i", i, 
				         GLtypeToString (type), long_name, location);
			}
		} else {
			int location = glGetUniformLocation (shaderID, name);
			log->more("  %i) type:%s name:%s location:%i", i, 
			         GLtypeToString (type), name, location);
		}
	}
	
	logShaderInfo (shaderID);
}

const char* ShaderManager::GLtypeToString (GLenum &type) {
	switch (type) {
		case GL_BOOL:              return "bool";
		case GL_INT:               return "int";
		case GL_FLOAT:             return "float";
		case GL_FLOAT_VEC2:        return "vec2";
		case GL_FLOAT_VEC3:        return "vec3";
		case GL_FLOAT_VEC4:        return "vec4";
		case GL_FLOAT_MAT2:        return "mat2";
		case GL_FLOAT_MAT3:        return "mat3";
		case GL_FLOAT_MAT4:        return "mat4";
		case GL_SAMPLER_2D:        return "sampler2D";
		case GL_SAMPLER_3D:        return "sampler3D";
		case GL_SAMPLER_CUBE:      return "samplerCube";
		case GL_SAMPLER_2D_SHADOW: return "sampler2DShadow";
		default: break;
	}
	return "other";
}



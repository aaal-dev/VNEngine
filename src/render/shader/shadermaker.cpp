#include "shadermaker.hpp"

Log* ShaderMaker::log = nullptr;
//ConfigManager* ShaderManager::configManager = nullptr;

// ----------------------------------------------------------- ShaderManager -- 

ShaderMaker::ShaderMaker(){
	log = Log::get();
}

ShaderMaker::~ShaderMaker(){}

// ------------------------------------------------------ public.ShaderMaker --

GLuint ShaderMaker::make(std::string const &vertexShaderFilepath, 
                         std::string const &fragmentShaderFilepath,
                         std::string const &geometryShaderFilepath) {
	GLuint vertexShaderID   = load(vertexShaderFilepath, GL_VERTEX_SHADER);
	GLuint fragmentShaderID = load(fragmentShaderFilepath, GL_FRAGMENT_SHADER);
	GLuint geometryShaderID = (geometryShaderFilepath.empty()) 
		? 0 
		: load(geometryShaderFilepath, GL_GEOMETRY_SHADER);
	
	log->info("Linking program");
	
	GLuint programId = glCreateProgram();
	glAttachShader(programId, vertexShaderID);
	glAttachShader(programId, fragmentShaderID);
	if (geometryShaderID) glAttachShader(programId, geometryShaderID);
	glLinkProgram(programId);
	
	// Check the program
	checkProgram(programId);
	
//	glDetachShader(programId, vertexShaderID);
//	glDetachShader(programId, fragmentShaderID);
//	if (geometryShaderID) glDetachShader(programId, geometryShaderID);
	
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
	if (geometryShaderID) glDeleteShader(geometryShaderID);
	return programId;
}


GLuint ShaderMaker::load(std::string const &filepath, GLenum shaderType) {
	std::string shaderSource = FileUtils::readTextFile(filepath);
	
	if (shaderSource.empty()){
		log->error("Impossible to open %s", filepath.data());
		return 0;
	}
	
	log->info("Loading shader %s", filepath.data());
	
	GLuint shaderID = glCreateShader(shaderType);
	GLchar const *files[] = {shaderSource.data()};
	glShaderSource(shaderID, 1, files, NULL);
	glCompileShader(shaderID);
	checkShader(shaderID); // Check the shader
	return shaderID;
}

bool ShaderMaker::isValid (GLuint &programId) {
	glValidateProgram (programId);
	int params = -1;
	glGetProgramiv (programId, GL_VALIDATE_STATUS, &params);
	log->info("program %i GL_VALIDATE_STATUS = %i", programId, params);
	if (GL_TRUE != params) {
		checkProgram (programId);
		return false;
	}
	return true;
}

// --------------------------------------------------- private:ShaderMaker --

// Log functions
void ShaderMaker::checkShader(GLuint &shaderID) {
	GLint result {GL_FALSE};
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		log->error("Something wrong.");
	}
	
	int length {0};
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
	if ( length > 0 ){
		std::vector<char> message(length+1);
		glGetShaderInfoLog(shaderID, length, NULL, &message[0]);
		log->error("%s", &message[0]);
	}
}

void ShaderMaker::checkProgram(GLuint &programId) {
	GLint result {GL_FALSE};
	glGetProgramiv(programId, GL_LINK_STATUS, &result);
	if (result == GL_FALSE) {
		log->error("Something wrong.");
	}
	
	int length {0};
	glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &length);
	if ( length > 0 ){
		std::vector<char> message(length+1);
		glGetProgramInfoLog(programId, length, NULL, &message[0]);
		log->error("%s", &message[0]);
	}
}

void ShaderMaker::logAllShaderInfo (GLuint &programId) {
	log->info("--------------------\nshader program %i info:", programId);
	int params = -1;
	glGetProgramiv (programId, GL_LINK_STATUS, &params);
	log->more("GL_LINK_STATUS = %i", params);
	
	glGetProgramiv (programId, GL_ATTACHED_SHADERS, &params);
	log->more("GL_ATTACHED_SHADERS = %i", params);
	
	glGetProgramiv (programId, GL_ACTIVE_ATTRIBUTES, &params);
	log->more("GL_ACTIVE_ATTRIBUTES = %i", params);
	for (GLuint i = 0; i < (GLuint)params; i++) {
		char name[64];
		int max_length = 64;
		int actual_length = 0;
		int size = 0;
		GLenum type;
		glGetActiveAttrib (programId, i, max_length, &actual_length, &size, 
		                   &type, name);
		if (size > 1) {
			for (int j = 0; j < size; j++) {
				char long_name[128];
				sprintf (long_name, "%s[%i]", name, j);
				int location = glGetAttribLocation (programId, long_name);
				log->more("  %i) type:%s name:%s location:%i", i, 
				         GLtypeToString (type), long_name, location);
			}
		} else {
			int location = glGetAttribLocation (programId, name);
			log->more("  %i) type:%s name:%s location:%i", i, 
			         GLtypeToString (type), name, location);
		}
	}
	
	glGetProgramiv (programId, GL_ACTIVE_UNIFORMS, &params);
	log->more("GL_ACTIVE_UNIFORMS = %i", params);
	for (GLuint i = 0; i < (GLuint)params; i++) {
		char name[64];
		int max_length = 64;
		int actual_length = 0;
		int size = 0;
		GLenum type;
		glGetActiveUniform (programId, i, max_length, &actual_length, &size, 
		                    &type, name);
		if (size > 1) {
			for (int j = 0; j < size; j++) {
				char long_name[128];
				sprintf (long_name, "%s[%i]", name, j);
				int location = glGetUniformLocation (programId, long_name);
				log->more("  %i) type:%s name:%s location:%i", i, 
				         GLtypeToString (type), long_name, location);
			}
		} else {
			int location = glGetUniformLocation (programId, name);
			log->more("  %i) type:%s name:%s location:%i", i, 
			         GLtypeToString (type), name, location);
		}
	}
	
	int length {0};
	glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &length);
	if ( length > 0 ){
		std::vector<char> message(length+1);
		glGetProgramInfoLog(programId, length, NULL, &message[0]);
		log->error("%s", &message[0]);
	}
}

const char* ShaderMaker::GLtypeToString (GLenum &type) {
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



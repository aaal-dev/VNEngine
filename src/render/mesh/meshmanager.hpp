#pragma once

#include <vector>

#include "glad/glad.h"

#include <glm/glm.hpp>

#include "../../log/log.hpp"
#include "../shader/shader.hpp"
#include "vertex.hpp"


class MeshManager {
	using Index = std::map<std::string, unsigned int>;
	
	// Variables
	static Log*  log;
	
	// Functions
	             
	
public:
	glm::mat4 normalization = glm::mat4(1.0);
	glm::mat4 transformation = glm::mat4(1.0);
	
	// Functions
	std::vector<Vertex> createQuad(vec3 position, vec2 size, vec3 origin, 
	                               float textureID, vec4 color);
	void loadModel(const std::string &model_filepath);
	
	void   setMesh();
	void   cleanup();
	
	 MeshManager();
	~MeshManager();
};

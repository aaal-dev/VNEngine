#pragma once

#include <deque>
#include <vector>
#include <cstring>
#include <map>

// GLAD
#include "glad/glad.h"

// GLFW
#include <GLFW/glfw3.h>

// GLM
#include <glm/gtc/matrix_transform.hpp>

// Inner classes
#include "../log/log.hpp"
#include "../config/configmanager.hpp"
#include "../control/controlmanager.hpp"
#include "../maths/maths.hpp"

#include "mesh/entity.hpp"
#include "mesh/frame.hpp"
#include "mesh/mesh.hpp"
#include "mesh/sprite.hpp"

struct CameraFrame {
	unsigned char* data;
	int width;
	int height;
};

class RenderManager {
public:
	// ---------------------------------------------------- public.Variables --
	GLsizei width;
	GLsizei height;
	GLsizei aspectRatio;
	mat4 orthographicMatrix;
	mat4 perspectiveMatrix;
	GLboolean *data;
	std::deque<Mesh*>   meshes;
	
	// ---------------------------------------------------- public.Functions -- 
	bool init();
	void update();
	void reset();
	void draw();
	void cleanup();
	void changeViewport(int bX, int bY, int eX, int eY);
	void setDrawProperties(std::map<std::string, bool> boolFromGui);
	
	
private:
	// --------------------------------------------------- private.Variables --
	static Log *log;
	acb::Section *config {nullptr};
	static ControlManager *controlManager;
	
	// --------------------------------------------------- private.Functions -- 
	void   logGLparams();
	
	
public:
	RenderManager();
	~RenderManager();
};

#pragma once


#include <cstring>
#include <list>
#include <map>
#include <vector>

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "../log/log.hpp"
#include "../config/configmanager.hpp"
#include "../control/controlmanager.hpp"
#include "../maths/maths.hpp"

#include "mesh/entity.hpp"
#include "mesh/frame.hpp"
#include "mesh/mesh.hpp"
#include "mesh/sprite.hpp"
#include "render.hpp"

struct CameraFrame {
	unsigned char* data;
	int width;
	int height;
};

class RenderManager {
public:
// -------------------------------------------------------- public.variables --
	
	GLsizei  width{1024};
	GLsizei  height{768};
	GLsizei  aspectRatio{0};
	mat4  orthographicMatrix;
	mat4  perspectiveMatrix;
	std::unique_ptr<Render> render;
	std::list<std::unique_ptr<Mesh>>  meshes;
	
// -------------------------------------------------------- public.functions --
	
	bool init();
	void update();
	void reset();
	void draw();
	void cleanup();
	void changeViewport(int bX, int bY, int eX, int eY);
	void setDrawProperties(std::map<std::string, bool> boolFromGui);
	
private:
// ------------------------------------------------------- private.variables --
	
	static Log *log;
	acb::Section *config {nullptr};
	static ControlManager *controlManager;
	
// ------------------------------------------------------- private.functions --
	
	void  createMockUpObjects();
	std::unique_ptr<Mesh> convertToMesh(std::vector<std::unique_ptr<Entity>> &entities);
	void   logGLparams();
	
public:
	RenderManager();
	~RenderManager();
};

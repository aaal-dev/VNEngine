#pragma once

#include <iostream>
#include <list>
#include <memory>
#include <vector>

#include "glad/glad.h"

#include "../log/log.hpp"
#include "../control/controlmanager.hpp"
#include "../maths/maths.hpp"
#include "../time/timemanager.hpp"
#include "camera.hpp"
#include "mesh/mesh.hpp"

class Render {
public:
// -------------------------------------------------------- public.functions --
	void  reset();
	void  update();
	void  submit(std::list<std::unique_ptr<Mesh>> meshes);
	void  draw();
	
	void  translate(vec3 v);
	void  rotate(mat4 m);
	void  scale(vec3 v);
	void  done();
	
	
private:
// ------------------------------------------------------- private.variables --
	static Log *log;
	acb::Section *config {nullptr};
	static TimeManager *timeManager;
	
	Camera  camera;
	std::list<std::unique_ptr<Mesh>>  meshes;
	
	
public:
	Render();
	virtual ~Render();
};

#include "rendermanager.hpp"

Log* RenderManager::log = nullptr;
ControlManager* RenderManager::controlManager = nullptr;

// ----------------------------------------------------------- RenderManager -- 

RenderManager::RenderManager () {
	log = Log::get();
//	controlManager = ControlManager::get();
	
	ConfigManager manager;
	config = manager.createSection("Render");
}

RenderManager::~RenderManager () {}

// ---------------------------------------------------- public:RenderManager -- 

bool RenderManager::init() {
	log->begin("RENDER MANAGER initializing...");
	
	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		log->error("Failed to initialize OpenGL context.");
		return false;
	}
	
	log->info("Renderer: %s", glGetString (GL_RENDERER));
	log->info("OpenGL version supported %s", glGetString (GL_VERSION));
	
	logGLparams ();
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
	
	render = std::make_unique<Render>();
	
	log->done("RENDER MANAGER initialized");
	return true;
}

void RenderManager::update () {
//	Configuration::Section* config = configManager->find("Video");
//	width = config->getValue<int>("width");
//	height = config->getValue<int>("height");
	//render.update();
	//render.submit(renderManager.meshes);
}

void RenderManager::draw() {
	//render.reset();
	//render.draw();
}

void RenderManager::changeViewport(int bX, int bY, int eX, int eY) {
	glViewport(bX, bY, eX, eY);
}

// --------------------------------------------------- private:RenderManager -- 

void RenderManager::createMockUpObjects() {
	// ------------------------------------------------------ MOCKUP OBJECTS --
	// Setting up test sprites
	std::vector<std::unique_ptr<Entity>> entities;
	for (int i = 1; i < 8; i+=1) {
		auto sprite = std::make_unique<Sprite>();
		sprite->name = "plane";
		sprite->position = vec3(i, 1, i);
		sprite->size = vec3(7, 7, 0);
		sprite->origin = vec3(-1, -1, 0);
		sprite->baseColor = RGBA(0.0f, 1.0f, 0.0f, 1.0f);
		sprite->visible = true;
		sprite->create();
		entities.push_back(std::move(sprite));
	}
	
	// Extract vertices and indices from sprites 
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	unsigned int offset = 0;
	for (auto const &entity : entities) {
		for (auto vertex : entity->vertices) {
			vertices.push_back(vertex); 
		}
		for (const auto &index : entity->indices) {
			indices.push_back(index + offset);
		}
		offset += entity->vertices.size();
	}
	
	// Convert sprites to mesh objects 
	auto mesh = std::make_unique<Mesh>();
	mesh->vao.bind();
	{
		mesh->vbo.create(&vertices.front(), vertices.size(), 3);
		mesh->vbo.bind(); {
			mesh->vbo.setAttribute(0, 3, GL_FLOAT, GL_FALSE, 
				reinterpret_cast<const GLvoid*>(0));
			mesh->vbo.setAttribute(1, 2, GL_FLOAT, GL_FALSE, 
				reinterpret_cast<const GLvoid*>(offsetof(Vertex, texCoords)));
			mesh->vbo.setAttribute(2, 1, GL_FLOAT, GL_FALSE, 
				reinterpret_cast<const GLvoid*>(offsetof(Vertex, texID)));
			mesh->vbo.setAttribute(3, 3, GL_FLOAT, GL_FALSE, 
				reinterpret_cast<const GLvoid*>(offsetof(Vertex, normal)));
			mesh->vbo.setAttribute(4, 4, GL_UNSIGNED_BYTE, GL_TRUE, 
				reinterpret_cast<const GLvoid*>(offsetof(Vertex, color)));
		}
		mesh->vbo.unbind();
		mesh->ebo.create(&indices.front(), indices.size());
	}
	mesh->vao.unbind();
	mesh->shader.load("../data/shaders/mesh.vert", "../data/shaders/mesh.frag");
	mesh->texture.load("001.png");
	
	meshes.push_back(std::move(mesh));
	
	// -------------------------------------------------- end:MOCKUP OBJECTS --
}

void RenderManager::logGLparams () {
	 GLenum params[] = {
		 GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
		 GL_MAX_CUBE_MAP_TEXTURE_SIZE,
		 GL_MAX_DRAW_BUFFERS,
		 GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
		 GL_MAX_TEXTURE_IMAGE_UNITS,
		 GL_MAX_TEXTURE_SIZE,
		 GL_MAX_VARYING_FLOATS,
		 GL_MAX_VERTEX_ATTRIBS,
		 GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
		 GL_MAX_VERTEX_UNIFORM_COMPONENTS,
		 GL_MAX_VIEWPORT_DIMS,
		 GL_STEREO,
	};
	const char* names[] = {
		"GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS",
		"GL_MAX_CUBE_MAP_TEXTURE_SIZE",
		"GL_MAX_DRAW_BUFFERS",
		"GL_MAX_FRAGMENT_UNIFORM_COMPONENTS",
		"GL_MAX_TEXTURE_IMAGE_UNITS",
		"GL_MAX_TEXTURE_SIZE",
		"GL_MAX_VARYING_FLOATS",
		"GL_MAX_VERTEX_ATTRIBS",
		"GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS",
		"GL_MAX_VERTEX_UNIFORM_COMPONENTS",
		"GL_MAX_VIEWPORT_DIMS",
		"GL_STEREO",
	};
	
	log->info("GL Context Params:");
	//char msg[256];
	
	// integers - only works if the order is 0-10 integer return types
	for (int i = 0; i < 10; i++) {
		int v = 0;
		glGetIntegerv (params[i], &v);
		log->more("%s %i", names[i], v);
	}
	
	// others
	int v[2];
	v[0] = v[1] = 0;
	glGetIntegerv (params[10], v);
	log->more("%s %i %i", names[10], v[0], v[1]);
	unsigned char s = 0;
	glGetBooleanv (params[11], &s);
	log->more("%s %u", names[11], (unsigned int) s);
	log->more("-----------------------------");
}


/* ============================================================== DEPRECATED == 

void RenderManager::draw() {
	float aspect_ratio = (float)width / (float)height;
	
	for (const auto &mesh : meshManager.meshes) {
		if (mesh.visible) {
			mesh.shader.enable();
			mesh.vao->bind();
			//GLuint modelMatrixID = glGetUniformLocation(mesh.shaderID, "model");
			//mat4 mesh_transform = mesh.normalization * mesh.transformation;
			//glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &mesh_transform.elements[0]);
			
			//GLuint viewMatrixID = glGetUniformLocation(mesh.shaderID, "view");
			//glm::mat4 view = glm::lookAt(glm::vec3(15.0, 5.0, 0.0), glm::vec3(0.0, 5.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
			//glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &view[0][0]);
			
			//GLuint projectionMatrixID = glGetUniformLocation(mesh.shaderID, "projection");
			//glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspect_ratio, 0.5f, 100.0f);
			//glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &projection[0][0]);
			
			//mesh.texture.bind();
			//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			
			mesh.ebo.bind();
			//glBufferSubData(GL_ARRAY_BUFFER, 0, mesh.vertices.size() * sizeof(Vertex), &mesh.vertices.front());
			
			mesh.shader.setUniformMat4("projection", mat4::orthographic(0, width, height, 0, 0, 1000));
			mesh.shader.setUniform4f("color", vec4(1.0f, 1.0f, 0.0f, 1.0f));
			vec2 mousePos = vec2(((float)controlManager->mouse.x / (float)width - 0.5f), (0.5f - (float)controlManager->mouse.y / (float)height ));
			mesh.shader.setUniform2f("light_pos", mousePos);
			
			glDrawElements(GL_TRIANGLES, sizeof(mesh.indices), GL_UNSIGNED_INT, 0);
			
			mesh.ebo.unbind();
			mesh.vao.unbind();
			mesh.shader.disable();
		}
	}
}

================================================================= DEPRECATED */

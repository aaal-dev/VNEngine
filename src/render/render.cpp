#include "render.hpp"

Log* Render::log = nullptr;
TimeManager* Render::timeManager = nullptr;

// ------------------------------------------------------------------ Render -- 

Render::Render () {
	log = Log::get();
	
	timeManager = TimeManager::get();
	camera.position = vec3(-2.0f, 0.0f, 3.0f);
	camera.front = vec3(0.0f, 0.0f, -1.0f);
	camera.worldUp = vec3(0.0f, 1.0f, 0.0f);
	camera.yaw = -90.0f;
	camera.pitch = 0.0f;
	camera.calculate();
}

Render::~Render () {}

// ----------------------------------------------------------- public.Render -- 

void Render::reset () {
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

void Render::update () {
	camera.update();
}

void Render::submit (std::deque<Mesh*> meshes) {
	this->meshes = meshes;
}

void Render::draw () {
	while (meshes.empty()) {
		Mesh* mesh = meshes.front(); {
			mesh->vao.bind();
			mesh->ebo.bind();
			// Reloading shader by key 'R' for testing purpose
//			if (controlManager->keyboard.key[KEY_R] == true) {
//				controlManager->keyboard.key[KEY_R] = false;
//				mesh->shader.reload();
//			}
			mesh->shader.enable();
			mesh->shader.setUniformMat4("projection", camera.orthographicMatrix);
			//mesh->shader.setUniformMat4("view_matrix", camera.lookAtMatrix);
			
			//glActiveTexture(GL_TEXTURE0);
			//mat4 mat = mat4::translation(vec3(mousePos, 0));
			//mat *= mat4::rotation(controlManager->mouse.x, mat4::ROTATION_Z);
			//mesh->shader.setUniformMat4("model_matrix", mat);
			
			
//			mesh->shader.setUniform2f("light_pos", controlManager->mouse.offset);
			//mesh->shader.setUniform2f("mouse", mousePos);
			mesh->texture.bind();
			
//			glViewport(0, 0, controlManager->screen.w, controlManager->screen.h);
			glDrawElements(GL_TRIANGLES, mesh->ebo.count(), GL_UNSIGNED_INT, 0);
			
			mesh->texture.unbind();
			mesh->shader.disable();
			mesh->ebo.unbind();
			mesh->vao.unbind();
		}
		meshes.pop_front();
	}
}

void Render::translate (vec3 v) {}

void Render::rotate (mat4 m) {}

void Render::scale (vec3 v) {}

void Render::done() {}

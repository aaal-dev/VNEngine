#include "meshmanager.hpp"

Log* MeshManager::log = nullptr;

//// ---- MeshManager ----------------------------------------------------- ////

MeshManager::MeshManager () {
	log = Log::get();
}

MeshManager::~MeshManager () {
	cleanup();
}

//// ---- public:MeshManager ---------------------------------------------- ////

std::vector<Vertex> MeshManager::createQuad(vec3 position, 
                                            vec2 size, 
                                            vec3 origin, 
                                            float textureID,
                                            vec4 color) {
	float x = position.x - 0.5f * size.w * (1 + origin.x);
	float y = position.y - 0.5f * size.h * (1 + origin.y);
	float z = position.z;
	Vertex v0;
	v0.position = { x, y, z };
	v0.texCoords = { 0.0f, 0.0f };
	v0.texID = textureID;
	v0.normal = { 0.0f, 0.0f, 0.0f };
	//v0.color = color;
	
	Vertex v1;
	v1.position = { x, y + size.h, z };
	v1.texCoords = { 0.0f, 1.0f };
	v1.texID = textureID;
	v1.normal = { 0.0f, 0.0f, 0.0f };
	//v1.color = color;
	
	Vertex v2;
	v2.position = { x + size.w, y + size.h, z };
	v2.texCoords = { 1.0f, 1.0f };
	v2.texID = textureID;
	v2.normal = { 0.0f, 0.0f, 0.0f };
	//v2.color = color;
	
	Vertex v3;
	v3.position = { x + size.w, y, z };
	v3.texCoords = { 1.0f, 0.0f };
	v3.texID = textureID;
	v3.normal = { 0.0f, 0.0f, 0.0f };
	//v3.color = color;
	
	return { v0, v1, v2, v3 };
}

void MeshManager::cleanup() {
	// Cleanup vbo
}

//// ---- private:MeshManager --------------------------------------------- ////

//// ==== DEPRECATE ======================================================= ////
/*
 * 
void RenderManager::setHeadModelMesh() {
	Mesh headModel;
	headModel.name = "head";
	//headModel.load_model("../data/model/cartoon/head.obj");
	//headModel.load_model("../data/model/female/female.obj");
	//headModel.load_shader( "../data/shaders/shader2.vert", "../data/shaders/shader2.frag" );
	
	headModel.shader.enable();
	
	GLuint l_positionMatrixID = glGetUniformLocation(headModel.shader.id, "l_position");
	glm::vec3 l_position = glm::vec3(10.0f, 15.0f, 10.0f);
	glUniform3fv(l_positionMatrixID, 1, &l_position[0]);
	
	GLuint l_colorMatrixID = glGetUniformLocation(headModel.shader.id, "l_color");
	glm::vec3 l_color = glm::vec3(1.0f, 1.0f, 1.0f);
	glUniform3fv(l_colorMatrixID, 1, &l_color[0]);
	
	GLuint colorMatrixID = glGetUniformLocation(headModel.shader.id, "color");
	vec3 m_color = headModel.baseColor;
	glUniform3fv(colorMatrixID, 1, &m_color.x);
	
	headModel.vbo.generate();
	headModel.vbo.bind();
	glBufferData(GL_ARRAY_BUFFER, headModel.vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
	
	headModel.vao.generate();
	headModel.vao.bind();
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(offsetof(Vertex, normal)));
	
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(offsetof(Vertex, texCoords)));
	
	// Set up index
	headModel.ebo.generate();
	headModel.ebo.bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, headModel.indices.size() * sizeof(unsigned int), &headModel.indices.front(), GL_STATIC_DRAW);
}

Mesh MeshManager::createPlane (vec3 pos, float width, float height, float texID) {
	Mesh mesh;
	
	mesh.vao.generate();
	mesh.vao.bind();
	
	// Setup vertices
	mesh.vbo.generate();
	mesh.vbo.bind();
	//mesh.vertices = createQuad(pos, width, height, texID);
	mesh.vertices1 = {  0.0f,  0.5f, 0.0f,
	                    0.5f,  0.0f, 0.0f,
	                    0.0f, -0.5f, 0.0f,
	                   -0.5f,  0.0f, 0.0f };
	glBufferData(GL_ARRAY_BUFFER, mesh.vertices1.size() * sizeof(GLfloat), &mesh.vertices1.front(), GL_STATIC_DRAW);
	
	
	// Setup indices
	mesh.ebo.generate();
	mesh.ebo.bind();
	mesh.indices = { 0, 1, 2, 2, 3, 0 };
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mesh.indices), &mesh.indices.front(), GL_STATIC_DRAW);
	mesh.ebo.unbind();
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)(0));
	
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(offsetof(Vertex, texID)));
	
	//glEnableVertexAttribArray(2);
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(offsetof(Vertex, texCoords)));
	
	//glEnableVertexAttribArray(3);
	//glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(offsetof(Vertex, normal)));
	
	//mesh.texture.generate(GL_TEXTURE_2D);
	//mesh.texture.bind();
	
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	mesh.vbo.unbind();
	
	mesh.vao.unbind();
	return mesh;
}

*/

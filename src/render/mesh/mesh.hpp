#pragma once

#include "buffer/vertexarray.hpp"
#include "buffer/vertexbuffer.hpp"
#include "buffer/elementbuffer.hpp"
#include "../shader/shader.hpp"
#include "../texture/texture.hpp"

struct Mesh {
	  VertexArray   vao;
	 VertexBuffer   vbo;
	ElementBuffer   ebo;
	       Shader   shader;
	      Texture   texture;
	
	          Mesh() {}
	virtual  ~Mesh() {}
};

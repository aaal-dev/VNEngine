#pragma once

#include <string>
#include <vector>

#include "../../maths/maths.hpp"
#include "../shader/shader.hpp"
#include "../texture/texture.hpp"
#include "vertex.hpp"

struct Entity {
	std::string name;
	vec3 position;
	vec3 size;
	vec3 origin;
	RGBA baseColor;
	
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	
	bool visible = true;
	GLuint indicesOffset;
	Shader shader;
	Texture texture;
	mat4 normalization;
	mat4 transformation;
	
	inline const vec3& getPosition() const {
		return position;
	}
	inline const vec3& getSize() const {
		return size;
	}
	inline const vec3& getOrigin() const {
		return origin;
	}
	inline const RGBA& getBaseColor() const {
		return baseColor;
	}
	
	inline unsigned int color(RGBA color) {
		unsigned int r = color.r * 255.0f;
		unsigned int g = color.g * 255.0f;
		unsigned int b = color.b * 255.0f;
		unsigned int a = color.a * 255.0f;
		return a << 24 | b << 16 | g << 8 | r;
	}
	
	virtual void create() = 0;
	
	Entity() {}
	Entity
	(std::string const &name, vec3 position, vec3 size, vec3 origin, RGBA color)
		: name(name)
		, position(position)
		, size(size)
		, origin(origin)
		, baseColor(color) {}
	
	virtual ~Entity() {}
};

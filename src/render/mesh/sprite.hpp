#pragma once

// Inner classes
#include "entity.hpp"

struct Sprite : public Entity {
	void create() {
		float x = position.x - 0.5f * size.w * (1 + origin.x);
		float y = position.y - 0.5f * size.h * (1 + origin.y);
		float z = position.z - 0.5f * size.d * (1 + origin.z);
		
		Vertex v0;
		v0.position = { x + size.w, y + size.h, z };
		v0.texCoords = { 1.0f, 1.0f };
		v0.texID = texture.id();
		v0.normal = { 0.0f, 0.0f, 0.0f };
		v0.color = color(baseColor);
		
		Vertex v1;
		v1.position = { x, y + size.h, z };
		v1.texCoords = { 0.0f, 1.0f };
		v1.texID = texture.id();
		v1.normal = { 0.0f, 0.0f, 0.0f };
		v1.color = color(baseColor);
		
		Vertex v2;
		v2.position = { x, y, z };
		v2.texCoords = { 0.0f, 0.0f };
		v2.texID = texture.id();
		v2.normal = { 0.0f, 0.0f, 0.0f };
		v2.color = color(baseColor);
		
		Vertex v3;
		v3.position = { x + size.w, y, z };
		v3.texCoords = { 1.0f, 0.0f };
		v3.texID = texture.id();
		v3.normal = { 0.0f, 0.0f, 0.0f };
		v3.color = color(baseColor);
		
		vertices = { v0, v1, v2, v3 };
		indices = { 0, 1, 2, 2, 3, 0 };
	}
	
	Sprite() {}
	Sprite(std::string name, vec3 position, vec3 size, vec3 origin, RGBA color) 
	: Entity(name, position, size, origin, color) {
		
		
		
	}
};

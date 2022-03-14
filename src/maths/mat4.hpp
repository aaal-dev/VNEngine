#pragma once

#include <cstring>

#include "utils.hpp"
#include "vec3.hpp"
#include "vec4.hpp"

struct mat4 {
	enum RotationAxis {
		ROTATION_X,
		ROTATION_Y,
		ROTATION_Z
	};
	
	union {
		float elements[16] = {0.0f};
		//vec4 columns[4];
	};
	
	mat4();
	mat4(float diagonal);
	mat4(float elements[16]);
	
	static mat4  identity();
	static mat4  orthographic(float left,   float right, 
	                          float bottom, float top,
	                          float near,   float far);
	static mat4  perspective(float fov, float aspect, float near, float far);
	static mat4  rotation(float angle, const vec3 &axis);
	static mat4  rotation(float angle, RotationAxis axis);
	static mat4  scale(const vec3 &v);
	static mat4  translation(const vec3 &v);
	static mat4  inverse(const mat4 &m);
	
	vec3  multiply(const vec3 &v) const;
	vec4  multiply(const vec4 &v) const;
	mat4& multiply(const mat4 &m);
	
	vec3  operator*=(const vec3 &v) const;
	vec4  operator*=(const vec4 &v) const;
	mat4& operator*=(const mat4 &m); 
	
};

vec3 operator*(mat4 m,  const vec3 &v);
vec4 operator*(mat4 m,  const vec4 &v);
mat4 operator*(mat4 m1, const mat4 &m2);

#pragma once

#include "vec3.hpp"

struct vec4 {
	union {
		struct {
			float x, y, z;
		};
		struct { 
			float r, g, b; 
		};
		vec3 xyz;
	};
	union { float w, a; };
	
	vec4();
	vec4(const vec4 &v);
	vec4(const float (&data)[4]);
	vec4(const vec2 &vector, const float &z, const float &w);
	vec4(const vec3 &vector, const float &w);
	vec4(const float &x, const float &y, const float &z, const float &w);
	
	vec4& add       (const vec4 &v);
	vec4& subtract  (const vec4 &v);
	vec4& multiply  (const vec4 &v);
	vec4& divide    (const vec4 &v);
	bool  compare   (const vec4 &v);
	
	vec4& operator+=(const vec4 &v);
	vec4& operator-=(const vec4 &v);
	vec4& operator*=(const vec4 &v);
	vec4& operator/=(const vec4 &v);
	bool  operator==(const vec4 &v);
	bool  operator!=(const vec4 &v);
};

vec4 operator+(vec4 v1, const vec4 &v2);
vec4 operator-(vec4 v1, const vec4 &v2);
vec4 operator*(vec4 v1, const vec4 &v2);
vec4 operator/(vec4 v1, const vec4 &v2);

typedef vec4 RGBA;

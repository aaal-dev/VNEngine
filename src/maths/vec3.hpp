#pragma once

#include "vec2.hpp"

struct vec3 {
	union {
		struct {
			float x, y;
		};
		struct {
			float r, g;
		};
		struct {
			float w, h;
		};
		vec2 xy;
	};
	union { float z, b, d; };
	
	vec3();
	vec3(const vec3 &v);
	vec3(const float (&data)[3]);
	vec3(const vec2 &vector, const float &z);
	vec3(const float &x, const float &y, const float &z);
	
	static float magnitude (const vec3 &v);
	static vec3  normalize (      vec3  v);
	static vec3  cross     (const vec3 &a, const vec3 &b);
	
	vec3& add       (const vec3 &v);
	vec3& subtract  (const vec3 &v);
	vec3& multiply  (const vec3 &v);
	vec3& multiply  (     float  f);
	vec3& divide    (const vec3 &v);
	vec3& divide    (     float  f);
	bool  compare   (const vec3 &v);
	
	vec3& operator+=(const vec3 &v);
	vec3& operator-=(const vec3 &v);
	vec3& operator*=(const vec3 &v);
	vec3& operator*=(     float  f);
	vec3& operator/=(const vec3 &v);
	vec3& operator/=(     float  f);
	bool  operator==(const vec3 &v);
	bool  operator!=(const vec3 &v);
};

vec3 operator+(vec3 v1, const vec3 &v2);
vec3 operator-(vec3 v1, const vec3 &v2);
vec3 operator*(vec3 v1, const vec3 &v2);
vec3 operator*(vec3 v1,      float  f );
vec3 operator/(vec3 v1, const vec3 &v2);
vec3 operator/(vec3 v1,      float  f );

typedef vec3 RGB;

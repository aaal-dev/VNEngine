#pragma once

#include <math.h>

struct vec2 {
	union {
		struct {
			float x, y;
		};
		struct {
			float w, h;
		};
	};
	
	vec2();
	vec2(const vec2 &v);
	vec2(const float (&d)[2]);
	vec2(const float &x, const float &y);
	
	vec2& add       (const vec2 &v);
	vec2& subtract  (const vec2 &v);
	vec2& multiply  (const vec2 &v);
	vec2& multiply  (     float  f);
	vec2& divide    (const vec2 &v);
	vec2& divide    (     float  f);
	bool  compare   (const vec2 &v);
	
	vec2& operator+=(const vec2 &v);
	vec2& operator-=(const vec2 &v);
	vec2& operator*=(const vec2 &v);
	vec2& operator*=(     float  f);
	vec2& operator/=(const vec2 &v);
	vec2& operator/=(     float  f);
	bool  operator==(const vec2 &v);
	bool  operator!=(const vec2 &v);
};

vec2 operator+(vec2 v1, const vec2 &v2);
vec2 operator-(vec2 v1, const vec2 &v2);
vec2 operator*(vec2 v1, const vec2 &v2);
vec2 operator*(vec2 v1,      float  f );
vec2 operator/(vec2 v1, const vec2 &v2);
vec2 operator/(vec2 v1,      float  f );

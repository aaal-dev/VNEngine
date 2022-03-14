#include "vec4.hpp"

vec4::vec4 () : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
vec4::vec4 (const vec4& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
vec4::vec4 (const float (&data)[4]) : x(data[0]), y(data[1]), z(data[2]), w(data[3]) {}
//vec4::vec4 (const vec2 &vector, const float &z, const float &w) : xy(vector), z(z), w(w) {}
vec4::vec4 (const vec2 &vector, const float &z, const float &w) : xyz(vector, z), w(w) {}
vec4::vec4 (const vec3 &vector, const float &w) : xyz(vector), w(w) {}
vec4::vec4 (const float &x, const float &y, const float &z, const float &w) : x(x), y(y), z(z), w(w) {}

// -------------------------------------------------------------------- vec4 -- 

vec4& vec4::add (const vec4 &v) {
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	this->w += v.w;
	return *this;
}

vec4& vec4::subtract (const vec4 &v) {
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	this->w -= v.w;
	return *this;
}

vec4& vec4::multiply (const vec4 &v) {
	this->x *= v.x;
	this->y *= v.y;
	this->z *= v.z;
	this->w *= v.w;
	return *this;
}

vec4& vec4::divide (const vec4 &v) {
	this->x /= v.x;
	this->y /= v.y;
	this->z /= v.z;
	this->w /= v.w;
	return *this;
}

bool  vec4::compare (const vec4 &v) {
	return x == v.x && y == v.y && z == v.z && w == v.w;
}

// --------------------------------------------------------- vec4::operators -- 

vec4& vec4::operator+= (const vec4 &v)    { return add(v);          }
vec4& vec4::operator-= (const vec4 &v)    { return subtract(v);     }
vec4& vec4::operator*= (const vec4 &v)    { return multiply(v);     }
vec4& vec4::operator/= (const vec4 &v)    { return divide(v);       }
bool  vec4::operator== (const vec4 &v)    { return compare(v);      }
bool  vec4::operator!= (const vec4 &v)    { return !compare(v);     }

vec4  operator+ (vec4 v1, const vec4 &v2) { return v1.add(v2);      }
vec4  operator- (vec4 v1, const vec4 &v2) { return v1.subtract(v2); }
vec4  operator* (vec4 v1, const vec4 &v2) { return v1.multiply(v2); }
vec4  operator/ (vec4 v1, const vec4 &v2) { return v1.divide(v2);   }

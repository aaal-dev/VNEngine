#include "vec3.hpp"

vec3::vec3 () : x(0.0f), y(0.0f), z(0.0f) {}
vec3::vec3 (const vec3& v) : x(v.x), y(v.y), z(v.z) {}
vec3::vec3 (const float (&data)[3]) : x(data[0]), y(data[1]), z(data[2]) {}
vec3::vec3 (const vec2 &v, const float &z) : xy(v), z(z) {}
vec3::vec3 (const float &x, const float &y, const float &z) : x(x), y(y), z(z) {}

// -------------------------------------------------------------------- vec3 -- 

float vec3::magnitude (const vec3 &v) {
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

vec3 vec3::normalize (vec3 v) {
	return v.divide(magnitude(v));
}

vec3 vec3::cross(const vec3& a, const vec3& b) {
	return vec3(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}

vec3& vec3::add (const vec3 &v) {
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	return *this;
}

vec3& vec3::subtract (const vec3 &v) {
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	return *this;
}

vec3& vec3::multiply (const vec3 &v) {
	this->x *= v.x;
	this->y *= v.y;
	this->z *= v.z;
	return *this;
}

vec3& vec3::multiply (float f) {
	this->x *= f;
	this->y *= f;
	this->z *= f;
	return *this;
}

vec3& vec3::divide (const vec3 &v) {
	this->x /= v.x;
	this->y /= v.y;
	this->z /= v.z;
	return *this;
}

vec3& vec3::divide (float f) {
	this->x /= f;
	this->y /= f;
	this->z /= f;
	return *this;
}

bool vec3::compare (const vec3 &v) {
	return x == v.x && y == v.y && z == v.z;
}

// --------------------------------------------------------- vec3::operators -- 

vec3& vec3::operator+= (const vec3 &v)    { return add(v);          }
vec3& vec3::operator-= (const vec3 &v)    { return subtract(v);     }
vec3& vec3::operator*= (const vec3 &v)    { return multiply(v);     }
vec3& vec3::operator*= (     float  f)    { return multiply(f);     }
vec3& vec3::operator/= (const vec3 &v)    { return divide(v);       }
vec3& vec3::operator/= (     float  f)    { return divide(f);       }
bool  vec3::operator== (const vec3 &v)    { return compare(v);      }
bool  vec3::operator!= (const vec3 &v)    { return !compare(v);     }

vec3  operator+ (vec3 v1, const vec3 &v2) { return v1.add(v2);      }
vec3  operator- (vec3 v1, const vec3 &v2) { return v1.subtract(v2); }
vec3  operator* (vec3 v1, const vec3 &v2) { return v1.multiply(v2); }
vec3  operator* (vec3 v ,      float  f ) { return v.multiply(f);   }
vec3  operator/ (vec3 v1, const vec3 &v2) { return v1.divide(v2);   }
vec3  operator/ (vec3 v ,      float  f ) { return v.divide(f);     }

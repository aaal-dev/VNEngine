#include "vec2.hpp"

vec2::vec2 () : x(0.0f), y(0.0f) {}
vec2::vec2 (const vec2 &v) : x(v.x), y(v.y) {}
vec2::vec2 (const float (&d)[2]) : x(d[0]), y(d[1]) {}
vec2::vec2 (const float &x, const float &y) : x(x), y(y) {}

// -------------------------------------------------------------------- vec2 -- 

vec2& vec2::add (const vec2 &v) {
	this->x += v.x;
	this->y += v.y;
	return *this;
}

vec2& vec2::subtract (const vec2 &v) {
	this->x -= v.x;
	this->y -= v.y;
	return *this;
}

vec2& vec2::multiply (const vec2 &v) {
	this->x *= v.x;
	this->y *= v.y;
	return *this;
}

vec2& vec2::multiply (float f) {
	this->x *= f;
	this->y *= f;
	return *this;
}

vec2& vec2::divide (const vec2 &v) {
	this->x /= v.x;
	this->y /= v.y;
	return *this;
}

vec2& vec2::divide (float f) {
	this->x /= f;
	this->y /= f;
	return *this;
}

bool  vec2::compare (const vec2 &v) {
	return x == v.x && y == v.y;
}

// --------------------------------------------------------- vec2::operators -- 

vec2& vec2::operator+= (const vec2 &v)    { return add(v);          }
vec2& vec2::operator-= (const vec2 &v)    { return subtract(v);     }
vec2& vec2::operator*= (const vec2 &v)    { return multiply(v);     }
vec2& vec2::operator*= (     float  f)    { return multiply(f);     }
vec2& vec2::operator/= (const vec2 &v)    { return divide(v);       }
vec2& vec2::operator/= (     float  f)    { return divide(f);       }
bool  vec2::operator== (const vec2 &v)    { return compare(v);      }
bool  vec2::operator!= (const vec2 &v)    { return !compare(v);     }

vec2  operator+ (vec2 v1, const vec2 &v2) { return v1.add(v2);      }
vec2  operator- (vec2 v1, const vec2 &v2) { return v1.subtract(v2); }
vec2  operator* (vec2 v1, const vec2 &v2) { return v1.multiply(v2); }
vec2  operator* (vec2 v ,      float  f ) { return v.multiply(f); }
vec2  operator/ (vec2 v1, const vec2 &v2) { return v1.divide(v2);   }
vec2  operator/ (vec2 v ,      float  f ) { return v.divide(f);   }
